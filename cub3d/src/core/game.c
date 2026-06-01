/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:01:19 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/16 19:01:30 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_player(t_game *game)
{
	t_player	*player;

	player = &game->player;
	handle_rotation(player, game->delta_time);
	handle_forward_movement(game, player, game->delta_time);
	handle_strafe_movement(game, player, game->delta_time);
}

int	game_loop(void *param)
{
	t_game			*game;
	struct timeval	current_time;

	game = (t_game *)param;
	if (!game)
		return (1);
	gettimeofday(&current_time, NULL);
	game->delta_time = (current_time.tv_sec - game->last_frame_time.tv_sec)
		+ (current_time.tv_usec - game->last_frame_time.tv_usec) / 1000000.0;
	game->last_frame_time = current_time;
	update_player(game);
	cast_all_rays(&game->raycast, &game->player, &game->map_data);
	render_3d_view(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win,
		game->mlx.img->img, 0, 0);
	return (0);
}

int	init_game(t_game *game, char *map_file)
{
	t_map	map;

	ft_memset(game, 0, sizeof(t_game));
	gettimeofday(&game->last_frame_time, NULL);
	game->delta_time = 0.0;
	init_map_data(&game->map_data);
	init_map(&map);
	if (parse_cub_file(map_file, &game->map_data) == 0)
		return (mlx_error_and_cleanup(game, "Failed to parse.cub file\n", 2));
	if (init_mlx(game) != 0)
		return (mlx_error_and_cleanup(game, "Failed to initialize MLX", 2));
	if (!load_all_textures(game))
		return (mlx_error_and_cleanup(game, "Failed to load textures", 3));
	init_player(&game->player, &game->map_data);
	init_minimap(&game->minimap);
	set_minimap_scale(game);
	if (init_raycast(game) != 0)
		return (mlx_error_and_cleanup(game, "Failed to initialize raycast", 4));
	setup_hooks(game);
	return (0);
}
