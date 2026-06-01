/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:52:19 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/07 16:41:40 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_map_data_colors(t_map_data *data)
{
	data->floor.r = -1;
	data->floor.g = -1;
	data->floor.b = -1;
	data->roof.r = -1;
	data->roof.g = -1;
	data->roof.b = -1;
}

void	init_map_data(t_map_data *data)
{
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->has_c = 0;
	data->has_f = 0;
	data->map_started = 0;
	init_map_data_colors(data);
}

void	init_map(t_map *map)
{
	ft_memset(map, 0, sizeof(*map));
	map->data = NULL;
	map->height = 0;
	map->width = 0;
}

void	init_player(t_player *player, t_map_data *config)
{
	player->movespeed = PLAYER_MOVE_SPEED;
	player->rotationspeed = PLAYER_ROTATION_SPEED;
	player->movesleft_or_right = 0;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->viewangle = 0;
	find_player_position(player, config);
}
