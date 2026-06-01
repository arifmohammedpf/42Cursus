/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calculate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:29:49 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/11 20:19:54 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_wall_height(t_wall_data *wall, t_ray *ray)
{
	double	distance_to_projection_plane;

	if (ray->distancetowall < 1.0)
		ray->distancetowall = 1.0;
	distance_to_projection_plane = (SCREENWIDTH / 2) / tan(M_PI / 6);
	wall->wall_height = (int)(TILE_SIZE / ray->distancetowall
			* distance_to_projection_plane);
	if (wall->wall_height > SCREENHEIGHT * 3)
		wall->wall_height = SCREENHEIGHT * 3;
	if (wall->wall_height < 1)
		wall->wall_height = 1;
	wall->wall_top = (SCREENHEIGHT / 2) - (wall->wall_height / 2);
	wall->wall_bottom = (SCREENHEIGHT / 2) + (wall->wall_height / 2);
	if (wall->wall_top < 0)
		wall->wall_top = 0;
	if (wall->wall_bottom >= SCREENHEIGHT)
		wall->wall_bottom = SCREENHEIGHT - 1;
}

void	calculate_texture_coords(t_wall_data *wall, t_ray *ray,
		t_img_data *texture)
{
	if (ray->was_hit_vertical)
	{
		wall->texture_x = (int)(ray->vertwallhit.y) % texture->width;
		if (ray->is_ray_facing_left)
			wall->texture_x = texture->width - wall->texture_x - 1;
		if (ray->is_ray_facing_right)
			wall->texture_num = 3;
		else
			wall->texture_num = 2;
	}
	else
	{
		wall->texture_x = (int)(ray->horzwallhit.x) % texture->width;
		if (ray->is_ray_facing_up)
			wall->texture_x = texture->width - wall->texture_x - 1;
		if (ray->is_ray_facing_down)
			wall->texture_num = 1;
		else
			wall->texture_num = 0;
	}
	if (wall->texture_x < 0)
		wall->texture_x = 0;
	if (wall->texture_x >= texture->width)
		wall->texture_x = texture->width - 1;
}

void	calculate_wall_data(t_wall_data *wall, t_ray *ray, t_img_data *texture)
{
	calculate_wall_height(wall, ray);
	calculate_texture_coords(wall, ray, texture);
}
