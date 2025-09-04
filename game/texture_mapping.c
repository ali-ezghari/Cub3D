/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:21:56 by mohalaou          #+#    #+#             */
/*   Updated: 2025/09/04 18:30:47 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

t_tex *determine_wall_texture(t_game *game, t_ray ray)
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

void my_mlx_pixel_put(t_game *data, int x, int y, unsigned int color)
{
    if (x < 0 || x >= data->width || y < 0 || y >= data->height)
        return;
        
    int bytes = data->img.bits_per_pixel / 8;
    unsigned char *dst = (unsigned char *)data->img.addr + y * data->img.line_length + x * bytes;

    dst[0] = color & 0xFF;
    dst[1] = (color >> 8) & 0xFF;
    dst[2] = (color >> 16) & 0xFF;
}

unsigned int get_texture_pixel(t_tex *texture, int x, int y)
{        
    int bytes_per_pixel = texture->bpp / 8;
    unsigned char *pixel = (unsigned char *)texture->addr + 
                          y * texture->line_len + 
                          x * bytes_per_pixel;
    
    unsigned int *color_ptr = (unsigned int *)pixel;
    return (*color_ptr);
}

int calculate_tex_x(t_ray ray, t_tex *texture)
{
    double wall_hit_x, wall_hit_y, offset, image_scale;
    int tex_x;
        
    wall_hit_x = ray.wall_hit_x;
    wall_hit_y = ray.wall_hit_y;
    
    if (ray.was_hit_vertical)
        offset = fmod(wall_hit_y, 64);
    else
        offset = fmod(wall_hit_x, 64);
    
    image_scale = (double)texture->height / 64;
    tex_x = offset * image_scale;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;
    if (tex_x < 0)
        tex_x = 0;

    if (!ray.was_hit_vertical && ray.is_facing_down)
        tex_x = texture->width - tex_x - 1;

    return (tex_x);
}

void draw_wall(t_game *game, int screen_x, int wall_start_y, int wall_height) 
{   
    unsigned    color;
    double      tex_y;
    double      scale;
    int         y_start;
    int         tex_x;
    int         y_end;
    
    tex_x = calculate_tex_x(game->rays[screen_x], game->texture);
    y_start = (game->height / 2) - (wall_height / 2);
    y_end = (game->height / 2) + (wall_height / 2);
    tex_y = 0;
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
        my_mlx_pixel_put(game, screen_x, y_start, color);
        tex_y += 1 / scale;
        y_start++;
    }
}
