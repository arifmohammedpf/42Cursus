/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:29:39 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 18:40:32 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_single_texture(t_game *game, int index, char *path)
{
	game->textures[index].img = mlx_xpm_file_to_image(game->mlx.mlx, path,
			&game->textures[index].width, &game->textures[index].height);
	if (!game->textures[index].img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (0);
	}
	game->textures[index].addr = mlx_get_data_addr(game->textures[index].img,
			&game->textures[index].bits_per_pixel,
			&game->textures[index].line_size, &game->textures[index].endian);
	return (1);
}

int	load_all_textures(t_game *game)
{
	char	*paths[4];
	int		i;

	paths[0] = game->map_data.no_path;
	paths[1] = game->map_data.so_path;
	paths[2] = game->map_data.we_path;
	paths[3] = game->map_data.ea_path;
	i = 0;
	while (i < 4)
	{
		if (!load_single_texture(game, i, paths[i]))
		{
			cleanup_textures(game);
			return (0);
		}
		i++;
	}
	return (1);
}
