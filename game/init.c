/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:06:26 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/13 17:45:27 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_ray(t_ray *ray, double ray_angle)
{
	ray->ray_angle = ray_angle;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->is_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->ray_angle < PI * 0.5
		||ray->ray_angle > PI * 1.5;
	ray->is_facing_left = !ray->is_facing_right;
	ray->was_hit_vertical = false;
}

static void	init_player_rotation(t_player *player, char spawn_dir)
{
	if (spawn_dir == 'S')
		player->rotation_angle = PI / 2;
	else if (spawn_dir == 'N')
		player->rotation_angle = 3 * PI / 2;
	else if (spawn_dir == 'W')
		player->rotation_angle = PI;
	else if (spawn_dir == 'E')
		player->rotation_angle = 0;
}

void	init_player(t_game *game, t_player *player)
{
	int	x;
	int	y;

	x = game->data->s_dir.y;
	y = game->data->s_dir.x;
	player->move_speed = 0.3;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->strafe_dir = 0;
	player->rotation_speed = 0.2 * (PI / 180);
	player->px = x * TILE_SIZE + TILE_SIZE / 2;
	player->py = y * TILE_SIZE + TILE_SIZE / 2;
	init_player_rotation(player, game->data->s_dir.dir);
}

void	init_game(t_game *game)
{
	game->width = 1280;
	game->height = 720;
	game->map_rows = game->data->map_length;
	game->map_cols = game->data->map_width;
	game->fov_angle = 60 * (PI / 180);
	game->distance_to_pl = (game->width / 2) / tan(game->fov_angle / 2);
	game->mlx = NULL;
	game->win = NULL;
	game->rays = NULL;
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		cleanup_and_exit(game, EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx,
			game->width, game->height, "cub3d");
	if (!game->win)
		cleanup_and_exit(game, EXIT_FAILURE);
	game->img.img = mlx_new_image(game->mlx,
			game->width, game->height);
	if (!game->img.img)
		cleanup_and_exit(game, EXIT_FAILURE);
	game->img.addr = mlx_get_data_addr(
			game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
		cleanup_and_exit(game, EXIT_FAILURE);
}
