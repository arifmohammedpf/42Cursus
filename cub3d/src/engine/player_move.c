/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:43:54 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 17:49:46 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= game->map_data.map_info.height)
		return (0);
	if (map_x >= (int)ft_strlen(game->map_data.map[map_y]))
		return (0);
	return (game->map_data.map[map_y][map_x] != '1');
}

static int	is_valid_position_with_margin(t_game *game, double x, double y)
{
	double	margin;

	margin = WALL_DIST;
	if (!is_valid_position(game, x - margin, y - margin)
		|| !is_valid_position(game, x + margin, y - margin)
		|| !is_valid_position(game, x - margin, y + margin)
		|| !is_valid_position(game, x + margin, y + margin))
		return (0);
	return (1);
}

void	handle_strafe_movement(t_game *game, t_player *player,
		double delta_time)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = PLAYER_MOVE_SPEED * delta_time;
	if (player->movesleft_or_right == 0)
		return ;
	new_x = player->position.x + cos(player->viewangle + M_PI / 2) * move_step
		* player->movesleft_or_right;
	new_y = player->position.y + sin(player->viewangle + M_PI / 2) * move_step
		* player->movesleft_or_right;
	if (is_valid_position_with_margin(game, new_x, player->position.y))
		player->position.x = new_x;
	if (is_valid_position_with_margin(game, player->position.x, new_y))
		player->position.y = new_y;
}

void	handle_rotation(t_player *player, double delta_time)
{
	double	rotation_speed;

	rotation_speed = PLAYER_ROTATION_SPEED * delta_time;
	player->viewangle += player->turndirection * rotation_speed;
	player->viewangle = normangle(player->viewangle);
}

void	handle_forward_movement(t_game *game, t_player *player,
		double delta_time)
{
	double	move_step;
	double	new_x;
	double	new_y;

	move_step = PLAYER_MOVE_SPEED * delta_time;
	if (player->walkdirection == 0)
		return ;
	new_x = player->position.x + cos(player->viewangle) * move_step
		* player->walkdirection;
	new_y = player->position.y + sin(player->viewangle) * move_step
		* player->walkdirection;
	if (is_valid_position_with_margin(game, new_x, player->position.y))
		player->position.x = new_x;
	if (is_valid_position_with_margin(game, player->position.x, new_y))
		player->position.y = new_y;
}
