/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:38:33 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/13 17:50:13 by mohalaou         ###   ########.fr       */
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
	if (!has_wall_at(game, new_player_x + FAR_AWAY, new_player_y + FAR_AWAY)
		&& !has_wall_at(game, new_player_x - FAR_AWAY, new_player_y - FAR_AWAY)
		&& !has_wall_at(game, new_player_x + FAR_AWAY, new_player_y - FAR_AWAY)
		&& !has_wall_at(game, new_player_x - FAR_AWAY, new_player_y + FAR_AWAY))
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

void	render_3d_walls(t_game *game)
{
	double	proj_wall_h;
	double	wall_height;
	double	corr_distance;
	int		y_start;
	int		i;

	i = 0;
	while (i < game->width)
	{
		corr_distance = game->rays[i].distance * cos(game->rays[i].ray_angle
				- game->player.rotation_angle);
		proj_wall_h = (TILE_SIZE / corr_distance) * game->distance_to_pl;
		wall_height = (int)proj_wall_h;
		y_start = (game->height / 2) - (proj_wall_h / 2);
		if (y_start < 0)
			y_start = 0;
		if (wall_height <= 0)
			continue ;
		game->texture = determine_wall_texture(game, game->rays[i]);
		if (game->texture && game->texture->addr)
			draw_wall(game, i, wall_height);
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
	draw_animated_part(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->img.img, 0, 0);
	return (0);
}
