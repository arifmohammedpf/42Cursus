/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:06:44 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/19 14:53:45 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <sys/time.h>

typedef struct s_wall_data
{
	int				wall_height;
	int				wall_top;
	int				wall_bottom;
	double			texture_x;
	int				texture_num;
}					t_wall_data;

typedef struct s_cordinates
{
	double			x;
	double			y;
}					t_cordinates;

typedef struct s_ray
{
	double			ray_angle;
	double			wall_hit_x;
	double			wall_hit_y;
	double			player_angle;
	double			distance;
	int				was_hit_vertical;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_left;
	int				is_ray_facing_right;
	int				wall_content;
	t_cordinates	horzwallhit;
	t_cordinates	vertwallhit;
	double			distancetowall;
	int				wallhitisvert;
}					t_ray;

typedef struct s_ray_cast
{
	double			fov_angle;
	int				num_rays;
	t_ray			*rays;
}					t_ray_cast;

typedef struct s_img_data
{
	void			*img;
	char			*addr;
	int				*int_addr;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
	int				width;
	int				height;
}					t_img_data;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	t_img_data		*img;
}					t_mlx;

typedef struct s_player
{
	t_cordinates	position;
	double			movespeed;
	double			viewangle;
	double			rotationspeed;
	int				movesleft_or_right;
	int				turndirection;
	int				walkdirection;
}					t_player;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_map
{
	char			**data;
	int				width;
	int				height;
}					t_map;

typedef struct s_map_data
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				has_c;
	int				has_f;
	int				has_no;
	int				has_so;
	int				has_we;
	int				has_ea;
	t_rgb			floor;
	t_rgb			roof;
	char			**map;
	t_map			map_info;
	int				map_started;
}					t_map_data;

typedef struct s_minimap_square
{
	int	start_x;
	int	start_y;
	int	size;
	int	color;
}	t_minimap_square;

typedef struct s_minimap
{
	int		size;
	int		scale;
	int		offset_x;
	int		offset_y;
	int		player_size;
	int		wall_color;
	int		floor_color;
	int		player_color;
	int		border_color;
}	t_minimap;

typedef struct s_game
{
	t_mlx			mlx;
	t_player		player;
	t_map_data		map_data;
	t_ray_cast		raycast;
	t_img_data		textures[4];
	t_minimap		minimap;
	double			delta_time;
	struct timeval	last_frame_time;
}					t_game;

typedef struct s_position
{
	int				i;
	int				j;
}					t_position;

typedef struct s_pixel_data
{
	int				strip_id;
	int				y;
	double			texture_pos;
}					t_pixel_data;

#endif