/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:26:52 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/11 20:28:58 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_safe_texture_y(int texture_y, int texture_height)
{
	if (texture_y < 0)
		return (0);
	if (texture_y >= texture_height)
		return (texture_height - 1);
	return (texture_y);
}

void	render_wall_pixel(t_game *game, t_wall_data *wall, t_img_data *texture,
		t_pixel_data pixel)
{
	int	texture_y;
	int	color;
	int	*img_data;
	int	line_length;

	img_data = (int *)game->mlx.img->addr;
	line_length = game->mlx.img->line_size / 4;
	texture_y = get_safe_texture_y((int)pixel.texture_pos % texture->height,
			texture->height);
	color = get_texture_pixel(texture, (int)wall->texture_x, texture_y);
	img_data[pixel.y * line_length + pixel.strip_id] = color;
}

void	init_texture_params(t_wall_data *wall, t_img_data *texture,
		double *texture_step, double *texture_pos)
{
	if (wall->wall_height <= 0)
		wall->wall_height = 1;
	*texture_step = (double)texture->height / wall->wall_height;
	*texture_pos = (wall->wall_top - SCREENHEIGHT / 2 + wall->wall_height / 2)
		* (*texture_step);
}

void	set_texture_number(t_wall_data *wall, t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_right)
			wall->texture_num = 3;
		else
			wall->texture_num = 2;
	}
	else
	{
		if (ray->is_ray_facing_down)
			wall->texture_num = 1;
		else
			wall->texture_num = 0;
	}
}
