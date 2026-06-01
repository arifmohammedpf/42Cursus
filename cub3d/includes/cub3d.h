/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:16:33 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/19 14:55:30 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../get_next_line/get_next_line.h"
# include "../includes/structures.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# if __APPLE__
#  include "../mlx_mac/mlx.h"
# elif __linux__
#  include "../mlx_linux/mlx.h"
# endif
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define SCREENWIDTH 1200
# define SCREENHEIGHT 700
# define PLAYER_MOVE_SPEED 3.0
# define PLAYER_ROTATION_SPEED 1.0
# define TILE_SIZE 1024
# define WALL_DIST 0.4

# if __APPLE__

typedef enum e_keys
{
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_ESC = 53,
	KEY_LEFT_ARROW = 123,
	KEY_RIGHT_ARROW = 124
}		t_keys;
# elif __linux__

typedef enum e_keys
{
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_W = 119,
	KEY_ESC = 65307,
	KEY_LEFT_ARROW = 65361,
	KEY_RIGHT_ARROW = 65363
}		t_keys;
# endif

/*----CORE FUNCTIONS----*/
int		game_loop(void *param);

/*----HOOKS----*/
int		esc_hook(t_game *game);
int		key_release_hook(int keycode, t_game *game);
int		key_hook(int keycode, t_game *game);
void	setup_hooks(t_game *game);

/*----INITIALIZATION----*/
void	init_map(t_map *data);
void	init_map_data(t_map_data *data);
void	init_player(t_player *player, t_map_data *config);
void	find_player_position(t_player *player, t_map_data *config);
int		init_mlx(t_game *game);
int		init_raycast(t_game *game);
int		init_game(t_game *game, char *map_file);

/* -----PARSING-----*/
int		parse_cub_file(const char *filename, t_map_data *config);
int		parse_line(t_map_data *config, char *line);
int		parse_color(char *color_str, t_rgb *color);
int		add_map_line(t_map_data *__map_data, char *line);
int		is_map_line(char *line);
void	free_split(char **split);
void	free_config(t_map_data *config);
int		validate_map_data(t_map_data *map_data);
int		rgb_to_decimal(t_rgb rgb);
int		check_map_enclosure(t_map_data *config);
void	cleanup_and_exit(t_game *game);
void	cleanup_raycast_data(t_game *game);
int		handle_map_line(t_map_data *map_data, char *line);
int		is_map_line(char *line);
int		parse_texture_line(t_map_data *map_data, char *trimmed);
int		parse_color_line(t_map_data *map_data, char *trimmed);
int		validate_map_line_content(char *line);
int		validate_single_map_line(char *line);
char	*expand_tabs_to_spaces(char *line);

/* ------VALIDATION------ */
int		validate_map_chars(t_map_data *config, int *player_count);
int		validate_map_structure(t_map_data *config);
int		validate_map(t_map_data *config);
int		validate_map_data(t_map_data *map_data);
int		validate_texture_files(t_map_data *config);
int		is_valid_number(char *str);
int		validate_rgb_components(t_rgb *color);
int		check_adjacent_boundary(t_map_data *config, t_position pos,
			t_position neighbor);
int		check_border_positions(t_map_data *config, int i, int j);
int		check_texture_duplicates(t_map_data *config, char *trimmed);

/* -----RAY CASTING-----*/
void	cast_all_rays(t_ray_cast *raycast, t_player *player,
			t_map_data *config);
int		load_all_textures(t_game *game);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
int		get_texture_pixel(t_img_data *texture, int x, int y);
int		create_rgb(int r, int g, int b);
void	calculate_wall_data(t_wall_data *wall, t_ray *ray, t_img_data *texture);
int		render_3d_view(t_game *game);
void	display_info(void);
double	find_horz_intersection(t_player *player, t_ray *ray,
			t_map_data *config);
double	find_vert_intersection(t_player *player, t_ray *ray,
			t_map_data *config);
void	render_ceiling_and_floor(t_game *game);
void	init_texture_params(t_wall_data *wall, t_img_data *texture,
			double *texture_step, double *texture_pos);
void	set_texture_number(t_wall_data *wall, t_ray *ray);
void	render_wall_pixel(t_game *game, t_wall_data *wall, t_img_data *texture,
			t_pixel_data pixel);
void	cleanup_textures(t_game *game);

/* -----RAY UTILS-----*/
double	normangle(double angle);
void	get_ray_direction(t_ray *ray);
int		has_wall_at(double x, double y, t_map_data *config);
double	get_dis(t_player *player, double x, double y, int check);
void	get_small_wall_hit(t_ray *ray, t_player *player, double horzdistance,
			double vertdistance);

/* -----PLAYER MOVEMENT----- */
void	update_player(t_game *game);
void	handle_rotation(t_player *player, double delta_time);
void	handle_forward_movement(t_game *game, t_player *player,
			double delta_time);
void	handle_strafe_movement(t_game *game, t_player *player,
			double delta_time);

int		mlx_error_and_cleanup(t_game *game, char *error_msg, int stage);

/* -----MINIMAP DRAWING PRIMITIVES  */
void	init_minimap(t_minimap *minimap);
void	draw_minimap_pixel(t_game *game, int x, int y, int color);
void	draw_minimap_square(t_game *game, t_minimap_square square);
void	draw_border_horizontal(t_game *game, int width, int height);
void	draw_border_vertical(t_game *game, int width, int height);
int		get_tile_color(t_game *game, char tile);
void	set_minimap_scale(t_game *game);
int		get_map_width(t_map_data *map_data);

/* -----MINIMAP COMPONENTS ----- */
void	draw_minimap_border(t_game *game);
void	draw_minimap_tiles(t_game *game);
void	draw_player_direction(t_game *game, int px, int py);
void	draw_minimap_player(t_game *game);
void	render_minimap(t_game *game);

#endif