/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:21:56 by mohalaou          #+#    #+#             */
/*   Updated: 2025/09/11 23:18:57 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_tex	*determine_wall_texture(t_game *game, t_ray ray)
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

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	int				bytes;
	unsigned char	*dst;

	bytes = img->bits_per_pixel / 8;
	dst = (unsigned char *)img->addr + y * img->line_length + x
		* bytes;
	dst[0] = color & 0xFF;
	dst[1] = (color >> 8) & 0xFF;
	dst[2] = (color >> 16) & 0xFF;
}

unsigned int	get_texture_pixel(t_tex *texture, int x, int y)
{
	int				bytes_per_pixel;
	unsigned int	*color_ptr;
	unsigned char	*pixel;

	bytes_per_pixel = texture->bpp / 8;
	pixel = (unsigned char *)texture->addr
		+ y * texture->line_len
		+ x * bytes_per_pixel;
	color_ptr = (unsigned int *)pixel;
	return (*color_ptr);
}

int	calculate_tex_x(t_ray ray, t_tex *texture)
{
	int	tex_x;

	double (wall_hit_x), (wall_hit_y), (offset), (image_scale);
	wall_hit_x = ray.wall_hit_x;
	wall_hit_y = ray.wall_hit_y;
	if (ray.was_hit_vertical)
		offset = fmod(wall_hit_y, TILE_SIZE);
	else
		offset = fmod(wall_hit_x, TILE_SIZE);
	image_scale = (double)texture->height / TILE_SIZE;
	tex_x = offset * image_scale;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	if ((!ray.was_hit_vertical && ray.is_facing_down)
		|| (ray.was_hit_vertical && ray.is_facing_left))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	draw_wall(t_game *game, int screen_x, int wall_height)
{
	double			tex_y;
	double			scale;
	unsigned int	color;

	int y_start, (tex_x), (y_end);
	tex_x = calculate_tex_x(game->rays[screen_x], game->texture);
	y_start = (game->height / 2) - (wall_height / 2);
	tex_y = 0;
	y_end = (game->height / 2) + (wall_height / 2);
	scale = (double)wall_height / game->texture->height;
	if (y_start < 0 || y_end > game->height)
	{
		y_start = 0;
		y_end = game->height;
		tex_y = ((wall_height / 2) - (game->height / 2)) / scale;
	}
	while (y_start < y_end)
	{
		color = get_texture_pixel(game->texture, tex_x, tex_y);
		if (screen_x < 0 || screen_x >= game->width
			|| y_start < 0 || y_start >= game->height)
			my_mlx_pixel_put(&game->img, screen_x, y_start, color);
		else
			continue;
		tex_y += 1 / scale;
		y_start++;
	}
}
