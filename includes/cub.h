/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohalaou <mohalaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:38:38 by aezghari          #+#    #+#             */
/*   Updated: 2025/09/13 17:52:32 by mohalaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <cub.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PATH_MAX 4096
# define PI 3.14159265359
# define ESC_KEY 65307
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define FAR_AWAY 10
# define SCALE_FACTOR 0.5
# define TILE_SIZE 64
# define ATTACK_KEY 102
# define CHANGE_WEAPON 99
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GREY 0x808080

typedef struct s_animation
{
    int current_frame;
    int total_frames;
    int frame_width;
    int frame_height;
    int frame_delay;
    int frame_timer;
} t_animation;

typedef struct s_tex
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_len;
	int					endian;
}						t_tex;

typedef struct s_horz
{
	double				x_intercept;
	double				y_intercept;
	double				step_x;
	double				step_y;
	double				next_x;
	double				next_y;
	bool				found;
}						t_horz;

typedef struct s_vert
{
	double				x_intercept;
	double				y_intercept;
	double				step_x;
	double				step_y;
	double				next_x;
	double				next_y;
	bool				found;
}						t_vert;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_ray
{
	double				wall_hit_x;
	double				wall_hit_y;
	double				distance;
	int					was_hit_vertical;
	double				ray_angle;
	bool				is_facing_up;
	bool				is_facing_down;
	bool				is_facing_right;
	bool				is_facing_left;
	int					wall_height;
	int					y_start;
	t_tex				*wall_texture;
	int					tex_x;
}						t_ray;

typedef struct s_player
{
	double				px;
	double				py;
	int					turn_dir;
	int					walk_dir;
	double				rotation_angle;
	double				move_speed;
	double				rotation_speed;
	int					strafe_dir;
	int					attack;
	int					weapon;					
	int					attack_frame;
	int 				attack_timer;
}						t_player;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	double				distance_to_pl;
	int					width;
	int					height;
	int					map_rows;
	int					map_cols;
	double				fov_angle;
	struct s_ray		*rays;
	struct s_player		player;
	struct s_img		img;
	struct s_info		*data;
	struct s_tex		*texture;
	t_tex				tex_north;
	t_tex				tex_south;
	t_tex				tex_east;
	t_tex				tex_west;
	t_tex				par;
	t_tex				knife_img[3];
	t_tex				gun_img[3];
	t_animation 		player_anim;
}						t_game;

typedef struct g_help_varible
{
	int					i;
	int					j;
	int					x;
	int					y;
	int					dir_set;
	char				next;
	char				c;
}						t_help_varible;

typedef struct s_day_check
{
	char				*named;
	int					checked;
}						t_argv_check;

typedef struct g_didraw_walltions
{
	char				no[PATH_MAX];
	char				so[PATH_MAX];
	char				we[PATH_MAX];
	char				ea[PATH_MAX];
}						t_didraw_walltions;

typedef struct g_color_data
{
	int					num_color;
	int					_rgb[3];
}						t_color_data;

typedef struct g_color
{
	t_color_data		ceil;
	t_color_data		floor;
}						t_color;

typedef struct g_start_dir
{
	char				dir;
	int					x;
	int					y;
}						t_start_dir;

typedef struct s_info
{
	t_didraw_walltions	dir;
	t_color				color;
	t_start_dir			s_dir;
	t_help_varible		*v;
	char				**map;
	int					map_width;
	int					map_length;
	char				**map_copy;
}						t_info;

/* parser_utils */
int						parser(int argc, char *file, t_info *data);
int						total_lines(char **arr);
int						ft_isspace(unsigned char c);
int						ft_is_all_spaces(const char *s);
int						ft_is_all_digits(const char *s);
int						ft_notmemchar(const char *str, char c, int count_sp);
void					free_str_array(char **arr);
char					**copy_array(char **original, int rows);
int						is_valid_color_struct(char *line);

/* init_color_dir */
int						skip_prefix(char *line);
int						parse_line(char *line, t_argv_check *argvs,
							t_info *data);
void					init_didraw_walltions(char *line, char *dir,
							t_info *data);
void					init_color(char *line, t_color_data *color,
							t_info *data);
void					validate_and_set_rgb(char **rgb, t_color_data *color,
							t_info *data);

/* check_map */
int						find_position(char **map, char target, int *x, int *y);
void					validate_border(char *line, t_info *data);
void					check_if_map_valid(int len, t_info *data);
void					validate_char(int i, int j, int *dir_set, t_info *data);
void					flood_fill(t_info *data, char target, int x, int y);

/* parser_utils_two */
int						is_map_line(char *line);
int						count_map_lines(int fd, t_info *data);
int						is_all_checked(t_argv_check *map_argv);
int						ft_notmemchar(const char *str, char c, int count_sp);
char					**copy_array(char **original, int rows);

/* parser_utils_three */
int						is_valid_name_file(char *argv);
void					exit_error(int status, char *message, t_info *data);
void					read_map(int fd, t_info *data, int total_map_lines,
							char *line);
void					replace_char_in_array(char **arr, char tar, char rep);
char					*skip_empty_lines(int fd, char *line);

// game functions
bool					find_vert_wall_hit(t_game *game, t_ray *ray, t_vert *v);
void					init_vert_ray(t_player *player, t_ray *ray, t_vert *v);
void					init_horz_ray(t_player *player, t_ray *ray, t_horz *h);
bool					find_horz_wall_hit(t_game *game, t_ray *ray, t_horz *h);
double					normalize_angle(double angle);
int						has_wall_at(t_game *game, int x, int y);
double					_2points_dist(double x0, double y0, double x1,
							double y1);
int						handle_keypress(int keycode, t_game *game);
int						handle_keyrelease(int keycode, t_game *game);
int						draw(t_game *game);
void					raycasting(t_game *game, t_player *player);
void					init_ray(t_ray *ray, double ray_angle);
void					cleanup_and_exit(t_game *game, int exit_code);
void					update(t_game *game, t_player *player);
void					init_player(t_game *game, t_player *player);
void					init_game(t_game *game);
void					init_mlx(t_game *game);
int						load_textures(t_game *game);
void					gets_data_addr_of_current_image(t_game *game);
int						mouse_move(int x, int y, t_game *game);
int						handle_destroy(t_game *game);

/* texture_mapping */
void					draw_wall(t_game *game, int screen_x, int wall_height);
int						calculate_tex_x(t_ray ray, t_tex *texture);
unsigned int			get_texture_pixel(t_tex *texture, int x, int y);
t_tex					*determine_wall_texture(t_game *game, t_ray ray);
void					my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);

/* minimap */
void 					draw_minimap(t_game *game);

/* animated sprite */
void 					draw_animated_part(t_game *game);


#endif
