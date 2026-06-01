/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:00:33 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/10 12:19:40 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_boundary_limits(t_map_data *config, t_position pos,
		t_position neighbor)
{
	if (neighbor.i < 0 || neighbor.i >= config->map_info.height)
	{
		printf("Error: Walkable area [%d,%d] adjacent to map boundary\n", pos.i,
			pos.j);
		return (0);
	}
	if (neighbor.j < 0 || neighbor.j >= (int)ft_strlen(config->map[neighbor.i]))
	{
		printf("Error: Walkable area [%d,%d] not properly ", pos.i, pos.j);
		printf("enclosed (adjacent to void)\n");
		return (0);
	}
	return (1);
}

static int	validate_adjacent_character(t_map_data *config, t_position pos,
		t_position neighbor)
{
	char	c;

	c = config->map[neighbor.i][neighbor.j];
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
	{
		if (c == ' ' || c == '\t')
		{
			printf("Error: Walkable area [%d,%d] adjacent to empty space - ",
				pos.i, pos.j);
			printf("map must be properly enclosed by walls\n");
		}
		else
		{
			printf("Error: Walkable area [%d,%d] adjacent to ", pos.i, pos.j);
			printf("invalid character '%c'\n", c);
		}
		return (0);
	}
	return (1);
}

int	check_adjacent_boundary(t_map_data *config, t_position pos,
		t_position neighbor)
{
	if (!check_boundary_limits(config, pos, neighbor))
		return (0);
	return (validate_adjacent_character(config, pos, neighbor));
}

int	check_border_positions(t_map_data *config, int i, int j)
{
	if (i == 0 || i == config->map_info.height - 1)
	{
		printf("Error: Walkable area at map border [%d,%d]\
			- map not enclosed by walls\n", i, j);
		return (0);
	}
	if (j == 0 || config->map[i][j + 1] == '\0')
	{
		printf("Error: Walkable area at line border [%d,%d] \
			- map not enclosed by walls\n", i, j);
		return (0);
	}
	return (1);
}
