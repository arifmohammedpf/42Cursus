/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:45:00 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 18:10:27 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap_border(t_game *game)
{
	int	map_width_pixels;
	int	map_height_pixels;

	map_width_pixels = get_map_width(&game->map_data) * game->minimap.scale;
	map_height_pixels = game->map_data.map_info.height * game->minimap.scale;
	if (map_width_pixels > game->minimap.size)
		map_width_pixels = game->minimap.size;
	if (map_height_pixels > game->minimap.size)
		map_height_pixels = game->minimap.size;
	draw_border_horizontal(game, map_width_pixels, map_height_pixels);
	draw_border_vertical(game, map_width_pixels, map_height_pixels);
}

void	draw_minimap_tiles(t_game *game)
{
	int	map_y;
	int	map_x;
	int	screen_x;
	int	screen_y;

	map_y = 0;
	while (map_y < game->map_data.map_info.height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(game->map_data.map[map_y]))
		{
			screen_x = game->minimap.offset_x + (map_x * game->minimap.scale);
			screen_y = game->minimap.offset_y + (map_y * game->minimap.scale);
			if (screen_x < game->minimap.offset_x + game->minimap.size
				&& screen_y < game->minimap.offset_y + game->minimap.size)
			{
				draw_minimap_square(game, (t_minimap_square){screen_x, screen_y,
					game->minimap.scale, get_tile_color(game,
						game->map_data.map[map_y][map_x])});
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_player_direction(t_game *game, int px, int py)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i <= 15)
	{
		x = px + (int)(cos(game->player.viewangle) * i);
		y = py + (int)(sin(game->player.viewangle) * i);
		if (x >= 0 && x < SCREENWIDTH && y >= 0 && y < SCREENHEIGHT)
			draw_minimap_pixel(game, x, y, game->minimap.player_color);
		i++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int	player_screen_x;
	int	player_screen_y;

	player_screen_x = game->minimap.offset_x + (int)(game->player.position.x
			* game->minimap.scale);
	player_screen_y = game->minimap.offset_y + (int)(game->player.position.y
			* game->minimap.scale);
	if (game->player.position.x >= 0 && game->player.position.y >= 0
		&& game->player.position.y < game->map_data.map_info.height
		&& game->player.position.x < ft_strlen(game->map_data.map\
[(int)game->player.position.y]))
	{
		draw_minimap_square(game, (t_minimap_square){player_screen_x
			- game->minimap.player_size / 2, player_screen_y
			- game->minimap.player_size / 2, game->minimap.player_size,
			game->minimap.player_color});
		draw_player_direction(game, player_screen_x, player_screen_y);
	}
}

void	render_minimap(t_game *game)
{
	draw_minimap_border(game);
	draw_minimap_tiles(game);
	draw_minimap_player(game);
}
