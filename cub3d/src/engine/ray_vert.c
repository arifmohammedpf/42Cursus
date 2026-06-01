/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:09 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:10 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_cordinates	find_vert_intercept(t_player *player, t_ray *ray)
{
	t_cordinates	intercept;

	intercept.x = floor(player->position.x * TILE_SIZE / TILE_SIZE) * TILE_SIZE
		+ (ray->is_ray_facing_right * TILE_SIZE);
	intercept.y = player->position.y * TILE_SIZE + (intercept.x
			- player->position.x * TILE_SIZE) * tan(ray->ray_angle);
	return (intercept);
}

t_cordinates	find_vert_step(t_ray *ray)
{
	t_cordinates	step;

	step.x = TILE_SIZE;
	if (ray->is_ray_facing_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray->ray_angle);
	if (ray->is_ray_facing_up && step.y > 0)
		step.y *= -1;
	if (ray->is_ray_facing_down && step.y < 0)
		step.y *= -1;
	return (step);
}

static int	check_vert_wall_hit(t_ray *ray, t_map_data *config,
		int check_isfacingleft)
{
	if (has_wall_at(ray->vertwallhit.x - check_isfacingleft, ray->vertwallhit.y,
			config))
		return (1);
	return (0);
}

static int	is_within_vert_bounds(t_ray *ray, t_map_data *config)
{
	return (ray->vertwallhit.x >= 0
		&& ray->vertwallhit.x < (config->map_info.width) * TILE_SIZE
		&& ray->vertwallhit.y >= 0
		&& ray->vertwallhit.y <= (config->map_info.height) * TILE_SIZE);
}

double	find_vert_intersection(t_player *player, t_ray *ray, t_map_data *config)
{
	t_cordinates	step;
	int				check_isfacingleft;
	int				getverthit;

	getverthit = 0;
	check_isfacingleft = ray->is_ray_facing_left;
	ray->vertwallhit = find_vert_intercept(player, ray);
	step = find_vert_step(ray);
	while (is_within_vert_bounds(ray, config))
	{
		if (check_vert_wall_hit(ray, config, check_isfacingleft))
		{
			getverthit = 1;
			break ;
		}
		ray->vertwallhit.x += step.x;
		ray->vertwallhit.y += step.y;
	}
	return (get_dis(player, ray->vertwallhit.x, ray->vertwallhit.y,
			getverthit));
}
