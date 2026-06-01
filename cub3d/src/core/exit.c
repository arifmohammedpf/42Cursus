/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:52:51 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/13 17:05:22 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mlx_error_and_cleanup(t_game *game, char *error_msg, int stage)
{
	printf("Error: %s\n", error_msg);
	if (stage >= 4)
	{
		cleanup_raycast_data(game);
		cleanup_textures(game);
	}
	if (stage >= 3)
		mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
	if (stage >= 2)
		free_config(&game->map_data);
	return (1);
}

static void	cleanup_game_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx.mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

static void	cleanup_main_image(t_game *game)
{
	if (game->mlx.img && game->mlx.img->img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img->img);
	if (game->mlx.img)
	{
		free(game->mlx.img);
		game->mlx.img = NULL;
	}
}

void	cleanup_raycast_data(t_game *game)
{
	if (game->raycast.rays)
	{
		free(game->raycast.rays);
		game->raycast.rays = NULL;
	}
}

void	cleanup_and_exit(t_game *game)
{
	cleanup_raycast_data(game);
	cleanup_game_textures(game);
	cleanup_main_image(game);
	if (game->mlx.mlx_win)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
		game->mlx.mlx_win = NULL;
	}
	if (game->mlx.mlx)
	{
		free(game->mlx.mlx);
		game->mlx.mlx = NULL;
	}
	free_config(&game->map_data);
}
