/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:32:45 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/04 18:32:18 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		cleanup_and_exit(game, EXIT_SUCCESS);
	else if (keycode == W_KEY)
		game->player.walk_dir = 1;
	else if (keycode == S_KEY)
		game->player.walk_dir = -1;
	else if (keycode == A_KEY)
		game->player.strafe_dir = -1;
	else if (keycode == D_KEY)
		game->player.strafe_dir = 1;
	else if (keycode == LEFT_ARROW)
		game->player.turn_dir = -1;
	else if (keycode == RIGHT_ARROW)
		game->player.turn_dir = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		cleanup_and_exit(game, EXIT_SUCCESS);
	else if (keycode == W_KEY || keycode == S_KEY)
		game->player.walk_dir = 0;
	else if (keycode == A_KEY || keycode == D_KEY)
		game->player.strafe_dir = 0;
	else if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
		game->player.turn_dir = 0;
	return (0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

double	_2points_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int load_textures(t_game *game)
{
    game->tex_west.img = mlx_xpm_file_to_image(game->mlx_connection,
		game->data->dir.we, &game->tex_west.width, &game->tex_west.height);
    if (!game->tex_west.img)
		return (1);
    game->tex_west.addr = mlx_get_data_addr(game->tex_west.img,
		&game->tex_west.bpp, &game->tex_west.line_len, &game->tex_west.endian);
    game->tex_east.img = mlx_xpm_file_to_image(game->mlx_connection,
		game->data->dir.ea, &game->tex_east.width, &game->tex_east.height);
    if (!game->tex_east.img)
		return (1);
    game->tex_east.addr = mlx_get_data_addr(game->tex_east.img,
		&game->tex_east.bpp, &game->tex_east.line_len, &game->tex_east.endian);
    game->tex_north.img = mlx_xpm_file_to_image(game->mlx_connection,
		game->data->dir.no, &game->tex_north.width, &game->tex_north.height);
    if (!game->tex_north.img)
		return (1);
    game->tex_north.addr = mlx_get_data_addr(game->tex_north.img,
		&game->tex_north.bpp, &game->tex_north.line_len, &game->tex_north.endian);
    game->tex_south.img = mlx_xpm_file_to_image(game->mlx_connection,
		game->data->dir.so, &game->tex_south.width, &game->tex_south.height);
    if (!game->tex_south.img)
		return (1);
    game->tex_south.addr = mlx_get_data_addr(game->tex_south.img,
		&game->tex_south.bpp, &game->tex_south.line_len, &game->tex_south.endian);
	return (0);
}
