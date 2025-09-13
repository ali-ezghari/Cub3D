/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:49:28 by mohalaou          #+#    #+#             */
/*   Updated: 2025/09/13 17:49:44 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void draw_animated_part(t_game *game) 
{
	static int frame = 0;
	static int frame_counter = 0;
	t_tex *img;
	if (game->player.attack == 1)
	{
		if (++frame_counter >= 60)
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
		img = &game->gun_img[frame];
	else
		img = &game->knife_img[frame];

	// Limit maximum scale to prevent huge weapons and crashes
	// double max_scale = 6.0;
	double scale_x = ((game->width * 3) / 6) / img->width;
	double scale_y = ((game->height * 5) / 6) / img->height;

	// if (scale_x > max_scale) scale_x = max_scale;
	// if (scale_y > max_scale) scale_y = max_scale;

	// Calculate actual scaled weapon size
	double scaled_weapon_width = img->width * scale_x;
	double scaled_weapon_height = img->height * scale_y;

	// Simple centering - put weapon in bottom-center of screen
	double weapon_center_x = game->width / 2.0;
	double weapon_center_y = game->height * 0.75;

	double start_win_x = weapon_center_x - scaled_weapon_width / 2.0;
	double start_win_y = weapon_center_y - scaled_weapon_height / 2.0;

	double end_win_x = start_win_x + scaled_weapon_width;
	double end_win_y = start_win_y + scaled_weapon_height;

	double tex_x, tex_y;
	unsigned int color;

	int x = 0, y = 0;
	while (start_win_x + x < end_win_x && start_win_x + x < game->width)
	{
		y = 0;
		while (start_win_y + y < end_win_y && start_win_y + y < game->height)
		{
			tex_x = (double)x / scale_x;
			tex_y = (double)y / scale_y;
			
			// Better bounds checking for texture coordinates
			if (tex_x >= 0 && tex_x < img->width && tex_y >= 0 && tex_y < img->height)
			{
				int win_x = (int)(start_win_x + x);
				int win_y = (int)(start_win_y + y);
				
				if (win_x >= 0 && win_x < game->width && win_y >= 0 && win_y < game->height)
				{
					color = get_texture_pixel(img, (int)(tex_x), (int)(tex_y));
					if (color != 0xFF000000)
						my_mlx_pixel_put(&game->img, win_x, win_y, color);
				}
			}
			y++;        
		}
		x++;
	}
}