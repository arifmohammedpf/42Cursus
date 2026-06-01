/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:01 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/03 11:44:02 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_cordinates	find_horz_intercept(t_player *player, t_ray *ray)
{
	t_cordinates	intercept;

	intercept.y = floor(player->position.y * TILE_SIZE / TILE_SIZE) * TILE_SIZE
		+ (ray->is_ray_facing_down * TILE_SIZE);
	intercept.x = player->position.x * TILE_SIZE + (intercept.y
			- player->position.y * TILE_SIZE) / tan(ray->ray_angle);
	return (intercept);
}

t_cordinates	find_horz_step(t_ray *ray)
{
	t_cordinates	step;

	step.y = TILE_SIZE;
	if (ray->is_ray_facing_up)
		step.y *= -1;
	step.x = TILE_SIZE / tan(ray->ray_angle);
	if (ray->is_ray_facing_left && step.x > 0)
		step.x *= -1;
	if (ray->is_ray_facing_right && step.x < 0)
		step.x *= -1;
	return (step);
}

static int	check_horz_wall_hit(t_ray *ray, t_map_data *config,
		int check_isfacingup)
{
	if (has_wall_at(ray->horzwallhit.x, ray->horzwallhit.y - check_isfacingup,
			config))
		return (1);
	return (0);
}

static int	is_within_horz_bounds(t_ray *ray, t_map_data *config)
{
	return (ray->horzwallhit.x >= 0
		&& ray->horzwallhit.x <= (config->map_info.width - 1) * TILE_SIZE
		&& ray->horzwallhit.y >= 0
		&& ray->horzwallhit.y <= (config->map_info.height - 1) * TILE_SIZE);
}

double	find_horz_intersection(t_player *player, t_ray *ray, t_map_data *config)
{
	t_cordinates	step;
	int				check_isfacingup;
	int				gethorhit;

	gethorhit = 0;
	check_isfacingup = ray->is_ray_facing_up;
	ray->horzwallhit = find_horz_intercept(player, ray);
	step = find_horz_step(ray);
	while (is_within_horz_bounds(ray, config))
	{
		if (check_horz_wall_hit(ray, config, check_isfacingup))
		{
			gethorhit = 1;
			break ;
		}
		ray->horzwallhit.x += step.x;
		ray->horzwallhit.y += step.y;
	}
	return (get_dis(player, ray->horzwallhit.x, ray->horzwallhit.y, gethorhit));
}
