/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimoham <arimoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:00:23 by arimoham          #+#    #+#             */
/*   Updated: 2025/06/13 17:00:24 by arimoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	validate_map_data(t_map_data *map_data)
{
	if (!map_data->no_path || !map_data->so_path || !map_data->we_path
		|| !map_data->ea_path)
	{
		printf("Error: Missing texture definitions\n");
		return (0);
	}
	if (map_data->floor.r == -1 || map_data->roof.r == -1)
	{
		printf("Error: Missing color definitions\n");
		return (0);
	}
	if (!map_data->map || map_data->map_info.height == 0)
	{
		printf("Error: Missing map\n");
		return (0);
	}
	if (!validate_map(map_data))
	{
		printf("Error: Invalid map structure\n");
		return (0);
	}
	return (1);
}

static int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

int	validate_map(t_map_data *map_data)
{
	int	player_count;

	if (!map_data->map)
		return (0);
	if (!validate_map_chars(map_data, &player_count))
		return (0);
	if (!validate_map_structure(map_data))
		return (0);
	if (!validate_texture_files(map_data))
	{
		printf("Error: Invalid texture files\n");
		return (0);
	}
	if (!validate_rgb_value(map_data->floor.r)
		|| !validate_rgb_value(map_data->floor.g)
		|| !validate_rgb_value(map_data->floor.b))
	{
		printf("Error: Invalid floor color values\n");
		return (0);
	}
	return (1);
}
