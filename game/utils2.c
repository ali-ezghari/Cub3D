/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:31:47 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/12 23:15:57 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	handle_destroy(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	float	sens;

	(void)y;
	center_x = game->width / 2;
	sens = 0.002;
	delta_x = x - center_x;
	game->player.rotation_angle += delta_x * sens;
	mlx_mouse_move(game->mlx, game->win, center_x, game->height / 2);
	return (0);
}

void	gets_data_addr_of_current_image(t_game *game)
{
	game->tex_west.addr = mlx_get_data_addr(game->tex_west.img,
			&game->tex_west.bpp, &game->tex_west.line_len,
			&game->tex_west.endian);
	game->tex_east.addr = mlx_get_data_addr(game->tex_east.img,
			&game->tex_east.bpp, &game->tex_east.line_len,
			&game->tex_east.endian);
	game->tex_north.addr = mlx_get_data_addr(game->tex_north.img,
			&game->tex_north.bpp, &game->tex_north.line_len,
			&game->tex_north.endian);
	game->tex_south.addr = mlx_get_data_addr(game->tex_south.img,
			&game->tex_south.bpp, &game->tex_south.line_len,
			&game->tex_south.endian);

	game->knife_img[0].addr = mlx_get_data_addr(game->knife_img[0].img,
			&game->knife_img[0].bpp, &game->knife_img[0].line_len,
			&game->knife_img[0].endian);		
				
	game->knife_img[1].addr = mlx_get_data_addr(game->knife_img[1].img,
			&game->knife_img[1].bpp, &game->knife_img[1].line_len,
			&game->knife_img[1].endian);	
					
	game->knife_img[2].addr = mlx_get_data_addr(game->knife_img[2].img,
			&game->knife_img[2].bpp, &game->knife_img[2].line_len,
			&game->knife_img[2].endian);

	game->gun_img[0].addr = mlx_get_data_addr(game->gun_img[0].img,
			&game->gun_img[0].bpp, &game->gun_img[0].line_len,
			&game->gun_img[0].endian);		
				
	game->gun_img[1].addr = mlx_get_data_addr(game->gun_img[1].img,
			&game->gun_img[1].bpp, &game->gun_img[1].line_len,
			&game->gun_img[1].endian);	
					
	game->gun_img[2].addr = mlx_get_data_addr(game->gun_img[2].img,
			&game->gun_img[2].bpp, &game->gun_img[2].line_len,
			&game->gun_img[2].endian);
	
	game->par.addr = mlx_get_data_addr(game->par.img,
			&game->par.bpp, &game->par.line_len,
			&game->par.endian);
}

int	has_wall_at(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x < 0 || map_x >= game->map_cols || map_y < 0
		|| map_y >= game->map_rows)
		return (1);
	return (game->data->map[map_y][map_x] == '1');
}

void	cleanup_and_exit(t_game *game, int exit_code)
{
	if (game->tex_west.img)
		mlx_destroy_image(game->mlx, game->tex_west.img);
	if (game->tex_north.img)
		mlx_destroy_image(game->mlx, game->tex_north.img);
	if (game->tex_south.img)
		mlx_destroy_image(game->mlx, game->tex_south.img);
	if (game->tex_east.img)
		mlx_destroy_image(game->mlx, game->tex_east.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	if (game->rays)
		free(game->rays);
	exit_error(-1, NULL, game->data);
	exit(exit_code);
}
