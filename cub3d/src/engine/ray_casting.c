/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:53:18 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/23 15:43:00 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cast_all_rays(t_ray_cast *raycast, t_player *player, t_map_data *config)
{
	double	ray_angle;
	double	angle_diff;
	int		count;

	angle_diff = raycast->fov_angle / raycast->num_rays;
	ray_angle = player->viewangle - (raycast->fov_angle / 2);
	count = 0;
	while (count < raycast->num_rays)
	{
		raycast->rays[count].ray_angle = normangle(ray_angle);
		raycast->rays[count].player_angle = player->viewangle;
		get_ray_direction(&raycast->rays[count]);
		get_small_wall_hit(&raycast->rays[count], player,
			find_horz_intersection(player, &raycast->rays[count], config),
			find_vert_intersection(player, &raycast->rays[count], config));
		ray_angle += angle_diff;
		count++;
	}
}
