/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:47:42 by mohalaou          #+#    #+#             */
/*   Updated: 2025/09/22 20:37:27 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_rec(t_game *game, int x, int y, int size)
{
	double	scale_factor;

	int (scaled_x), (scaled_y), (scaled_size), (i), (j);
	i = 0;
	j = 0;
	scale_factor = fmin(game->width / 3.0, game->height / 3.0) / (game->map_cols
			* TILE_SIZE);
	scaled_x = (int)(x * scale_factor);
	scaled_y = (int)(y * scale_factor);
	scaled_size = (int)(size * scale_factor);
	while (i <= scaled_size)
	{
		j = 0;
		while (j <= scaled_size)
		{
			if (i == 0 || j == 0)
				my_mlx_pixel_put(&game->img, scaled_x + i, scaled_y + j,
					COLOR_BLACK);
			else
				my_mlx_pixel_put(&game->img, scaled_x + i, scaled_y + j,
					game->data->v->color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game, t_player *player, int color)
{
	double	scale_factor;

	int (y), (x), (scaled_x), (scaled_y);
	scale_factor = fmin(game->width / 3.0, game->height / 3.0) / (game->map_cols
			* TILE_SIZE);
	y = -10;
	while (y <= 10)
	{
		x = -10;
		while (x <= 10)
		{
			if (x * x + y * y <= (10 * 10))
			{
				scaled_x = scale_factor * (player->px + x);
				scaled_y = scale_factor * (player->py + y);
				my_mlx_pixel_put(&game->img, scaled_x, scaled_y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int (x), (y), (tile_x), (tile_y);
	x = 0;
	while (game->data->map[x])
	{
		y = 0;
		while (game->data->map[x][y])
		{
			tile_x = y * TILE_SIZE;
			tile_y = x * TILE_SIZE;
			if (game->data->map[x][y] == '1')
				game->data->v->color = COLOR_WHITE;
			else
				game->data->v->color = COLOR_BLACK;
			draw_rec(game, tile_x, tile_y, TILE_SIZE);
			y++;
		}
		x++;
	}
	draw_player(game, &game->player, COLOR_RED);
}
