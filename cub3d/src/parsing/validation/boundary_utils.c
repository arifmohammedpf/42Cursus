/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_validate_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:09:49 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/19 11:51:09 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	init_direction_arrays(int *dx, int *dy)
{
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 1;
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
}

static int	check_walkable_enclosure(t_map_data *config, int i, int j)
{
	int			dx[4];
	int			dy[4];
	t_position	pos;
	t_position	neighbor;
	int			k;

	init_direction_arrays(dx, dy);
	pos.i = i;
	pos.j = j;
	k = 0;
	while (k < 4)
	{
		neighbor.j = j + dx[k];
		neighbor.i = i + dy[k];
		if (!check_adjacent_boundary(config, pos, neighbor))
			return (0);
		k++;
	}
	return (1);
}

static int	validate_walkable_position(t_map_data *config, int i, int j)
{
	if (!check_border_positions(config, i, j))
		return (0);
	if (!check_walkable_enclosure(config, i, j))
		return (0);
	return (1);
}

int	check_map_enclosure(t_map_data *config)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i < config->map_info.height)
	{
		j = 0;
		while (config->map[i][j])
		{
			c = config->map[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!validate_walkable_position(config, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
