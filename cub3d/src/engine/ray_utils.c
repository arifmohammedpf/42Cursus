/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:44:05 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/11 17:55:33 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normangle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

void	get_ray_direction(t_ray *ray)
{
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
	{
		ray->is_ray_facing_down = 1;
		ray->is_ray_facing_up = 0;
	}
	else
	{
		ray->is_ray_facing_down = 0;
		ray->is_ray_facing_up = 1;
	}
	if (ray->ray_angle < (M_PI / 2) || ray->ray_angle > (3 * M_PI / 2))
	{
		ray->is_ray_facing_right = 1;
		ray->is_ray_facing_left = 0;
	}
	else
	{
		ray->is_ray_facing_right = 0;
		ray->is_ray_facing_left = 1;
	}
}

int	has_wall_at(double x, double y, t_map_data *config)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > config->map_info.width * TILE_SIZE || y < 0
		|| y > config->map_info.height * TILE_SIZE)
		return (1);
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_y >= config->map_info.height || !config->map[map_y])
		return (1);
	if (map_x >= (int)ft_strlen(config->map[map_y]))
		return (1);
	return (config->map[map_y][map_x] == '1');
}

double	get_dis(t_player *player, double x, double y, int check)
{
	double	player_x;
	double	player_y;
	double	dx;
	double	dy;

	if (!check)
		return (__DBL_MAX__);
	player_x = player->position.x * TILE_SIZE;
	player_y = player->position.y * TILE_SIZE;
	dx = x - player_x;
	dy = y - player_y;
	return (sqrt((dx * dx) + (dy * dy)));
}

void	get_small_wall_hit(t_ray *ray, t_player *player, double horzdistance,
		double vertdistance)
{
	ray->wallhitisvert = 0;
	if (horzdistance <= vertdistance)
	{
		ray->distancetowall = horzdistance * cos(ray->ray_angle
				- player->viewangle);
		ray->wall_hit_x = ray->horzwallhit.x / TILE_SIZE;
		ray->wall_hit_y = ray->horzwallhit.y / TILE_SIZE;
		ray->was_hit_vertical = 0;
	}
	else if (horzdistance > vertdistance)
	{
		ray->wallhitisvert = 1;
		ray->distancetowall = vertdistance * cos(ray->ray_angle
				- player->viewangle);
		ray->wall_hit_x = ray->vertwallhit.x / TILE_SIZE;
		ray->wall_hit_y = ray->vertwallhit.y / TILE_SIZE;
		ray->was_hit_vertical = 1;
	}
	ray->distance = ray->distancetowall;
}
