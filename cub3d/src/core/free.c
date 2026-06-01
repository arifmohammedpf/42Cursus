/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:30:00 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 18:40:19 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	free_texture_paths(t_map_data *config)
{
	if (config->no_path)
		free(config->no_path);
	if (config->so_path)
		free(config->so_path);
	if (config->we_path)
		free(config->we_path);
	if (config->ea_path)
		free(config->ea_path);
}

static void	free_map_array(t_map_data *config)
{
	int	i;

	if (!config->map)
		return ;
	i = 0;
	while (i < config->map_info.height)
	{
		if (config->map[i])
			free(config->map[i]);
		i++;
	}
	free(config->map);
}

void	free_config(t_map_data *config)
{
	free_texture_paths(config);
	free_map_array(config);
	ft_memset(config, 0, sizeof(*config));
}

void	cleanup_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx.mlx, game->textures[i].img);
		i++;
	}
	if (game->mlx.img)
	{
		if (game->mlx.img->img)
			mlx_destroy_image(game->mlx.mlx, game->mlx.img->img);
		free(game->mlx.img);
	}
	if (game->raycast.rays)
		free(game->raycast.rays);
}
