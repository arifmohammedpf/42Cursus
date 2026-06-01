/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:01:14 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/19 14:50:38 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_map_line_content(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n\r");
	if (!trimmed)
		return (0);
	if (trimmed[0] == '\0')
	{
		printf("Error: Empty line found within map structure\n");
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

int	is_map_line(char *line)
{
	char	*ptr;
	int		has_map_chars;

	ptr = line;
	has_map_chars = 0;
	while (*ptr && *ptr != '\n' && *ptr != '\r')
	{
		if (*ptr == '1' || *ptr == '0' || *ptr == 'N' || *ptr == 'S'
			|| *ptr == 'E' || *ptr == 'W')
			has_map_chars = 1;
		else if (*ptr != ' ' && *ptr != '\t')
			return (0);
		ptr++;
	}
	return (has_map_chars);
}

int	handle_map_line(t_map_data *map_data, char *line)
{
	char	*trimmed;

	if (map_data->map_started)
	{
		if (!validate_map_line_content(line))
			return (0);
	}
	else
		map_data->map_started = 1;
	trimmed = ft_strtrim(line, "\n\r");
	if (!trimmed)
		return (0);
	if (!validate_single_map_line(trimmed))
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (add_map_line(map_data, line));
}

static char	**reallocate_map(t_map_data *map_data)
{
	char	**new_map;
	int		new_size;
	int		i;

	if (map_data->map_info.height == 0)
		new_size = 1;
	else
		new_size = map_data->map_info.height + 1;
	new_map = malloc(sizeof(char *) * (new_size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	if (map_data->map)
	{
		while (i < map_data->map_info.height)
		{
			new_map[i] = map_data->map[i];
			i++;
		}
		free(map_data->map);
	}
	return (new_map);
}

int	add_map_line(t_map_data *map_data, char *line)
{
	char	**new_map;
	char	*trimmed_line;
	char	*expanded_line;

	trimmed_line = ft_strtrim(line, "\n\r");
	if (!trimmed_line)
		return (0);
	expanded_line = expand_tabs_to_spaces(trimmed_line);
	free(trimmed_line);
	if (!expanded_line)
		return (0);
	new_map = reallocate_map(map_data);
	if (!new_map)
	{
		free(expanded_line);
		return (0);
	}
	new_map[map_data->map_info.height] = expanded_line;
	new_map[map_data->map_info.height + 1] = NULL;
	map_data->map = new_map;
	map_data->map_info.height++;
	if ((int)ft_strlen(expanded_line) > map_data->map_info.width)
		map_data->map_info.width = ft_strlen(expanded_line);
	return (1);
}
