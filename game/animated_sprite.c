/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:49:28 by mohalaou          #+#    #+#             */
/*   Updated: 2025/09/14 17:25:34 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_tex	*find_frame_image(t_game *game)
{
	static int	frame;
	static int	frame_counter;

	if (game->player.attack == 1)
	{
		if (++frame_counter >= 50)
		{
			frame_counter = 0;
			frame++;
		}
		if (frame >= 3)
		{
			frame = 0;
			game->player.attack = 0;
		}
	}
	if (game->player.weapon)
		return (&game->gun_img[frame]);
	else
		return (&game->knife_img[frame]);
}

void	init_animated_struct(t_game *game, t_tex *img)
{
	game->vari.scale_x = ((game->width * 3) / 6) / img->width;
	game->vari.scale_y = ((game->height * 5) / 6) / img->height;
	game->vari.scaled_weapon_width = img->width * game->vari.scale_x;
	game->vari.scaled_weapon_height = img->height * game->vari.scale_y;
	game->vari.weapon_center_x = game->width / 2.0;
	game->vari.weapon_center_y = game->height * 0.75;
	game->vari.start_win_x = game->vari.weapon_center_x
		- game->vari.scaled_weapon_width / 2.0;
	game->vari.start_win_y = game->vari.weapon_center_y
		- game->vari.scaled_weapon_height / 2.0;
	game->vari.end_win_x = game->vari.start_win_x
		+ game->vari.scaled_weapon_width;
	game->vari.end_win_y = game->vari.start_win_y
		+ game->vari.scaled_weapon_height;
}

void	draw_pixel_if_valid(t_game *game, t_tex *img, int x, int y)
{
	unsigned int	color;
	int				win_x;
	int				win_y;

	game->vari.tex_x = (double)x / game->vari.scale_x;
	game->vari.tex_y = (double)y / game->vari.scale_y;
	if (game->vari.tex_x >= 0 && game->vari.tex_x < img->width
		&& game->vari.tex_y >= 0 && game->vari.tex_y < img->height)
	{
		win_x = (int)(game->vari.start_win_x + x);
		win_y = (int)(game->vari.start_win_y + y);
		if (win_x >= 0 && win_x < game->width && win_y >= 0
			&& win_y < game->height)
		{
			color = get_texture_pixel(img, (int)(game->vari.tex_x),
					(int)(game->vari.tex_y));
			if (color != 0xFF000000)
				my_mlx_pixel_put(&game->img, win_x, win_y, color);
		}
	}
}

void	draw_animated_part(t_game *game)
{
	t_tex	*img;
	int		x;
	int		y;

	x = 0;
	y = 0;
	img = find_frame_image(game);
	init_animated_struct(game, img);
	while (game->vari.start_win_x + x < game->vari.end_win_x
		&& game->vari.start_win_x + x < game->width)
	{
		y = 0;
		while (game->vari.start_win_y + y < game->vari.end_win_y
			&& game->vari.start_win_y + y < game->height)
		{
			draw_pixel_if_valid(game, img, x, y);
			y++;
		}
		x++;
	}
}
