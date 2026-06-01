/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:53:08 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/19 15:27:44 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		write(1, "\033[38;5;196mgame over!!!\033[0m\n", 26);
		cleanup_and_exit(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->player.walkdirection = 1;
	if (keycode == KEY_S)
		game->player.walkdirection = -1;
	if (keycode == KEY_A)
		game->player.movesleft_or_right = -1;
	if (keycode == KEY_D)
		game->player.movesleft_or_right = 1;
	if (keycode == KEY_LEFT_ARROW)
		game->player.turndirection = -1;
	if (keycode == KEY_RIGHT_ARROW)
		game->player.turndirection = 1;
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.walkdirection = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		game->player.movesleft_or_right = 0;
	if (keycode == KEY_RIGHT_ARROW || keycode == KEY_LEFT_ARROW)
		game->player.turndirection = 0;
	return (0);
}

int	esc_hook(t_game *game)
{
	cleanup_and_exit(game);
	exit(0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.mlx_win, KEY_PRESS, 1L << 0, key_hook, game);
	mlx_hook(game->mlx.mlx_win, KEY_RELEASE, 1L << 1, key_release_hook, game);
	mlx_hook(game->mlx.mlx_win, DESTROY_NOTIFY, 0, esc_hook, game);
}
