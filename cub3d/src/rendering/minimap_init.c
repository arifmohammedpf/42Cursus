/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:45:00 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 17:51:20 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_minimap(t_minimap *minimap)
{
	minimap->size = 200;
	minimap->offset_x = 10;
	minimap->offset_y = 10;
	minimap->player_size = 6;
	minimap->wall_color = 0x404040;
	minimap->floor_color = 0xFFFFFF;
	minimap->player_color = 0xFF0000;
	minimap->border_color = 0x000000;
}

int	get_map_width(t_map_data *map_data)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < map_data->map_info.height)
	{
		current_width = ft_strlen(map_data->map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

void	set_minimap_scale(t_game *game)
{
	int	map_width;
	int	map_height;
	int	scale_x;
	int	scale_y;

	map_width = get_map_width(&game->map_data);
	map_height = game->map_data.map_info.height;
	scale_x = game->minimap.size / map_width;
	scale_y = game->minimap.size / map_height;
	if (scale_x < scale_y)
		game->minimap.scale = scale_x;
	else
		game->minimap.scale = scale_y;
	if (game->minimap.scale < 2)
		game->minimap.scale = 2;
	if (game->minimap.scale > 20)
		game->minimap.scale = 20;
}
