/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:53:32 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/16 19:30:08 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_empty_line(t_map_data *data, char *trimmed)
{
	free(trimmed);
	if (data->map_started)
	{
		printf("Error: Empty line found in/after map structure\n");
		return (0);
	}
	return (1);
}

static int	parse_identifier_line(t_map_data *map_data, char *trimmed)
{
	if (parse_texture_line(map_data, trimmed))
		return (1);
	if (parse_color_line(map_data, trimmed))
		return (1);
	if (ft_strlen(trimmed) > 0)
		printf("Error: Invalid line format: %s\n", trimmed);
	return (0);
}

static int	process_non_empty_line(t_map_data *data, char *line, char *trimmed)
{
	if (data->map_started)
	{
		free(trimmed);
		return (handle_map_line(data, line));
	}
	if (is_map_line(trimmed))
	{
		data->map_started = 1;
		free(trimmed);
		return (handle_map_line(data, line));
	}
	else if (!parse_identifier_line(data, trimmed))
	{
		free(trimmed);
		return (0);
	}
	free(trimmed);
	return (1);
}

int	parse_map_line(t_map_data *data, char *line, char *trimmed)
{
	if (is_map_line(trimmed))
	{
		if (!handle_map_line(data, line))
		{
			free(trimmed);
			return (0);
		}
		data->map_started = 1;
	}
	else if (data->map_started)
	{
		printf("Error: No elements allowed after map structure\n");
		free(trimmed);
		return (0);
	}
	else if (!parse_identifier_line(data, trimmed))
	{
		free(trimmed);
		return (0);
	}
	return (1);
}

int	parse_line(t_map_data *data, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\r\n");
	if (!trimmed)
		return (0);
	if (trimmed[0] == '\0')
		return (handle_empty_line(data, trimmed));
	return (process_non_empty_line(data, line, trimmed));
}
