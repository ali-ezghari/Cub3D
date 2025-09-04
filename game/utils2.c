/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:31:47 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/04 18:16:57 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	has_wall_at(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / game->tile_size;
	map_y = y / game->tile_size;
	if (map_x < 0 || map_x >= game->map_cols
		|| map_y < 0 || map_y >= game->map_rows)
		return (1);
	return (game->data->map[map_y][map_x] == '1');
}

void	cleanup_and_exit(t_game *game, int exit_code)
{
	if (game->tex_west.img)
		mlx_destroy_image(game->mlx_connection, game->tex_west.img);
	if (game->tex_north.img)
		mlx_destroy_image(game->mlx_connection, game->tex_north.img);
	if (game->tex_south.img)
		mlx_destroy_image(game->mlx_connection, game->tex_south.img);
	if (game->tex_east.img)
		mlx_destroy_image(game->mlx_connection, game->tex_east.img);
	if (game->img.img)
			mlx_destroy_image(game->mlx_connection, game->img.img);

	if (game->win_window)
		mlx_destroy_window(game->mlx_connection, game->win_window);
	if (game->mlx_connection)
		mlx_destroy_display(game->mlx_connection);
	if (game->mlx_connection)
		free(game->mlx_connection);
	if (game->rays)
		free(game->rays);
	exit_error(-1, NULL, game->data);
	exit(exit_code);
}
