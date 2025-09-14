/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:46:29 by mohalaou          #+#    #+#             */
/*   Updated: 2025/09/14 17:25:15 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	_2points_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
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
