/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:52:27 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/23 12:01:26 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
		player->viewangle = 3 * M_PI / 2;
	else if (direction == 'S')
		player->viewangle = M_PI / 2;
	else if (direction == 'E')
		player->viewangle = 0;
	else if (direction == 'W')
		player->viewangle = M_PI;
}

void	find_player_position(t_player *player, t_map_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (map_data->map[i][j] == 'N' || map_data->map[i][j] == 'S'
				|| map_data->map[i][j] == 'E' || map_data->map[i][j] == 'W')
			{
				player->position.x = j + 0.5;
				player->position.y = i + 0.5;
				set_player_direction(player, map_data->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
