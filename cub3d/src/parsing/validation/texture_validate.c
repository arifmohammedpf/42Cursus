/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:00:51 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/16 19:20:10 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	validate_single_texture(char *path, char *direction)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open %s texture: %s\n", direction, path);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_texture_duplicates(t_map_data *config, char *trimmed)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0 && config->no_path != NULL)
	{
		printf("Error: Duplicate North texture identifier\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "SO", 2) == 0 && config->so_path != NULL)
	{
		printf("Error: Duplicate South texture identifier\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "WE", 2) == 0 && config->we_path != NULL)
	{
		printf("Error: Duplicate West texture identifier\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "EA", 2) == 0 && config->ea_path != NULL)
	{
		printf("Error: Duplicate East texture identifier\n");
		return (0);
	}
	return (1);
}

int	validate_texture_files(t_map_data *config)
{
	if (!validate_single_texture(config->no_path, "North"))
		return (0);
	if (!validate_single_texture(config->so_path, "South"))
		return (0);
	if (!validate_single_texture(config->we_path, "West"))
		return (0);
	if (!validate_single_texture(config->ea_path, "East"))
		return (0);
	return (1);
}
