/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:38:33 by aezghari          #+#    #+#             */
/*   Updated: 2025/08/28 18:55:32 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	update(t_game *game, t_player *player)
{
	double	new_player_x;
	double	new_player_y;
	double	move_step;

	player->rotation_angle += player->turn_dir * player->rotation_speed;
	move_step = player->walk_dir * player->move_speed;
	new_player_x = player->px + cos(player->rotation_angle) * move_step;
	new_player_y = player->py + sin(player->rotation_angle) * move_step;
	if (player->strafe_dir != 0)
	{
		new_player_x += cos(player->rotation_angle + (PI / 2))
			* player->strafe_dir * player->move_speed;
		new_player_y += sin(player->rotation_angle + (PI / 2))
			* player->strafe_dir * player->move_speed;
	}
	if (!has_wall_at(game, new_player_x + 2, new_player_y + 2)
		&& !has_wall_at(game, new_player_x - 2, new_player_y - 2)
		&& !has_wall_at(game, new_player_x + 2, new_player_y - 2)
		&& !has_wall_at(game, new_player_x - 2, new_player_y + 2))
	{
		player->px = new_player_x;
		player->py = new_player_y;
	}
}

static void	ft_clear(t_game *game, int width, int height)
{
	int	total_pixels;
	int	i;
	int	*pixels;

	i = 0;
	pixels = (int *)game->img.addr;
	total_pixels = width * height;
	while (i < total_pixels / 2)
		pixels[i++] = game->data->color.ceil.num_color;
	while (i < total_pixels)
		pixels[i++] = game->data->color.floor.num_color;
}

t_tex *determine_wall_texture(t_game *game, t_ray ray)
{
    if (ray.was_hit_vertical)
    {
        if (ray.is_facing_left)
            return (&game->tex_west);
        else
            return (&game->tex_east);
    }
    else
    {
        if (ray.is_facing_up)
            return (&game->tex_north);
        else
            return (&game->tex_south);
    }
}

int determine_wall_color(t_ray ray)
{
	if (ray.was_hit_vertical)
    {
        if (ray.is_facing_left)
            return (COLOR_WEST);
        else
            return (COLOR_EAST);
    }
    else
    {
        if (ray.is_facing_up)
            return (COLOR_NORTH);
        else
            return (COLOR_SOUTH);
    }
}

void my_mlx_pixel_put(t_game *data, int x, int y, unsigned int color)
{
    if (x < 0 || x >= data->width || y < 0 || y >= data->height)
        return;
        
    int bytes = data->img.bits_per_pixel / 8;
    unsigned char *dst = (unsigned char *)data->img.addr + y * data->img.line_length + x * bytes;

    dst[0] = color & 0xFF;
    dst[1] = (color >> 8) & 0xFF;
    dst[2] = (color >> 16) & 0xFF;
    if (bytes == 4)
        dst[3] = (color >> 24) & 0xFF; 
}

unsigned int get_texture_pixel(t_tex *texture, int x, int y)
{        
    int bytes_per_pixel = texture->bpp / 8;
    unsigned char *pixel = (unsigned char *)texture->addr + 
                          y * texture->line_len + 
                          x * bytes_per_pixel;
    
    unsigned int *color_ptr = (unsigned int *)pixel;
    return *color_ptr;
}

int calculate_tex_x(t_ray ray, t_tex *texture)
{
    double wall_hit_x, wall_hit_y;
    double offset;
    int tex_x;
        
    wall_hit_x = ray.wall_hit_x;
    wall_hit_y = ray.wall_hit_y;
    
    if (ray.was_hit_vertical)
        offset = wall_hit_y - floor(wall_hit_y);
    else
        offset = wall_hit_x - floor(wall_hit_x);
    
    tex_x = (int)(offset * texture->width);
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;
    if (tex_x < 0)
        tex_x = 0;
    
    if (ray.was_hit_vertical && ray.is_facing_left)
        tex_x = texture->width - tex_x - 1;
    if (!ray.was_hit_vertical && ray.is_facing_up)
        tex_x = texture->width - tex_x - 1;
        
    return tex_x;
}

void rec(t_game *game, int screen_x, int wall_start_y, int wall_height, t_tex *texture)
{
    if (screen_x < 0 || screen_x >= game->width)
        return;
    if (wall_start_y >= game->height || wall_height <= 0)
        return;
    
    int tex_x = calculate_tex_x(game->rays[screen_x], texture);

    int wall_end_y = wall_start_y + wall_height;
    int screen_y = wall_start_y;

    while (screen_y < wall_end_y)
    {
        int wall_pixel = screen_y - wall_start_y;
        int tex_y = (wall_pixel * texture->height) / wall_height;
        if (tex_y >= texture->height)
            tex_y = texture->height - 1;
        if (tex_y < 0)
            tex_y = 0;
        
        unsigned color = get_texture_pixel(texture, tex_x, tex_y);
        my_mlx_pixel_put(game, screen_x, screen_y, color);
        screen_y++;
    }
}

void render_3d_walls(t_game *game)
{
    double proj_wall_h;
    double wall_height;
    double corr_distance;
    int y_start;
    int i;

	i = 0;

	while (i < game->width)
	{
		corr_distance = game->rays[i].distance
			* cos(game->rays[i].ray_angle - game->player.rotation_angle);
		proj_wall_h = (game->tile_size / corr_distance)
			* game->distance_to_pl;
		wall_height = (int)proj_wall_h;
		y_start = (game->height / 2) - (proj_wall_h / 2);
		if (y_start < 0)
			y_start = 0;
		if ((wall_height + y_start) > game->height)
			wall_height = game->height - y_start;
		if (wall_height <= 0)
			continue ;

        t_tex *texture = determine_wall_texture(game, game->rays[i]);
        if (texture && texture->addr)
            rec(game, i, y_start, wall_height, texture);
        
        i++;
	}
}


int	draw(t_game *game)
{
    if (!game)
        return (-1);
        
	ft_clear(game, game->width, game->height);
	update(game, &game->player);
	raycasting(game, &game->player);
	render_3d_walls(game);
	mlx_put_image_to_window(game->mlx_connection, game->win_window,
		game->img.img, 0, 0);
	return (0);
}