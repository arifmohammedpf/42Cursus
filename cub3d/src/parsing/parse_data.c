/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:01:09 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/16 19:35:24 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	assign_texture_path(char **path_ptr, char *trimmed, int offset)
{
	if (*path_ptr)
		free(*path_ptr);
	*path_ptr = ft_strtrim(trimmed + offset, " \t");
}

int	parse_texture_line(t_map_data *map_data, char *trimmed)
{
	if (!check_texture_duplicates(map_data, trimmed))
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		assign_texture_path(&map_data->no_path, trimmed, 3);
		map_data->has_no = 1;
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		assign_texture_path(&map_data->so_path, trimmed, 3);
		map_data->has_so = 1;
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		assign_texture_path(&map_data->we_path, trimmed, 3);
		map_data->has_we = 1;
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		assign_texture_path(&map_data->ea_path, trimmed, 3);
		map_data->has_ea = 1;
	}
	else
		return (0);
	return (1);
}

int	parse_color_line(t_map_data *map_data, char *trimmed)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		if (map_data->has_f)
		{
			printf("Error: Duplicate floor color definition\n");
			return (0);
		}
		if (!parse_color(trimmed + 2, &map_data->floor))
			return (0);
		map_data->has_f = 1;
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		if (map_data->has_c)
		{
			printf("Error: Duplicate ceiling color definition\n");
			return (0);
		}
		if (!parse_color(trimmed + 2, &map_data->roof))
			return (0);
		map_data->has_c = 1;
	}
	else
		return (0);
	return (1);
}
