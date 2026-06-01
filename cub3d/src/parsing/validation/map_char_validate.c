/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_char_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:00:40 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/16 15:31:56 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_single_map_line(char *line)
{
	char	*ptr;

	ptr = line;
	while (*ptr)
	{
		if (!is_valid_map_char(*ptr))
		{
			printf("Error: Invalid character '%c' in map\n", *ptr);
			return (0);
		}
		ptr++;
	}
	return (1);
}

int	validate_map_chars(t_map_data *config, int *player_count)
{
	int	i;
	int	j;

	i = 0;
	*player_count = 0;
	while (i < config->map_info.height)
	{
		j = 0;
		while (config->map[i][j])
		{
			if (!is_valid_map_char(config->map[i][j]))
			{
				printf
				("Error: Invalid character '%c' in map at position [%d,%d]\n",
					config->map[i][j], i, j);
				return (0);
			}
			if (is_player_char(config->map[i][j]))
				(*player_count)++;
			j++;
		}
		i++;
	}
	return (1);
}
