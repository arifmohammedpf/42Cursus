/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:12:43 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/07 16:50:06 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error: Invalid number of arguments.\n");
		printf("Usage: ./cub3D <map_file.cub>\n");
		return (1);
	}
	display_info();
	if (init_game(&game, av[1]) != 0)
		return (1);
	mlx_loop_hook(game.mlx.mlx, game_loop, &game);
	mlx_loop(game.mlx.mlx);
	if (mlx_destroy_window(game.mlx.mlx, game.mlx.mlx_win) != 0)
		return (mlx_error_and_cleanup(&game, "Error:\
			Failed to destroy window", 2));
	cleanup_and_exit(&game);
	free_config(&game.map_data);
	return (0);
}
