/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:00:46 by arimoham          #+#    #+#             */
/*   Updated: 2025/09/19 14:40:41 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	validate_map_structure(t_map_data *config)
{
	int	player_count;

	player_count = 0;
	if (!validate_map_chars(config, &player_count))
		return (0);
	if (player_count != 1)
	{
		printf("Error: Map must have exactly one player (found %d)\n",
			player_count);
		return (0);
	}
	return (check_map_enclosure(config));
}
