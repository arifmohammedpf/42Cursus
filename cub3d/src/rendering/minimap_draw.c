/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:00 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 18:03:09 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
	int	*img_data;
	int	line_length;

	if (x < 0 || x >= SCREENWIDTH || y < 0 || y >= SCREENHEIGHT)
		return ;
	img_data = (int *)game->mlx.img->addr;
	line_length = game->mlx.img->line_size / 4;
	img_data[y * line_length + x] = color;
}

void	draw_minimap_square(t_game *game, t_minimap_square square)
{
	int	x;
	int	y;

	y = square.start_y;
	while (y < square.start_y + square.size)
	{
		x = square.start_x;
		while (x < square.start_x + square.size)
		{
			draw_minimap_pixel(game, x, y, square.color);
			x++;
		}
		y++;
	}
}

void	draw_border_horizontal(t_game *game, int width, int height)
{
	int	x;

	x = game->minimap.offset_x - 1;
	while (x <= game->minimap.offset_x + width)
	{
		draw_minimap_pixel(game, x, game->minimap.offset_y - 1,
			game->minimap.border_color);
		draw_minimap_pixel(game, x, game->minimap.offset_y + height,
			game->minimap.border_color);
		x++;
	}
}

void	draw_border_vertical(t_game *game, int width, int height)
{
	int	y;

	y = game->minimap.offset_y - 1;
	while (y <= game->minimap.offset_y + height)
	{
		draw_minimap_pixel(game, game->minimap.offset_x - 1, y,
			game->minimap.border_color);
		draw_minimap_pixel(game, game->minimap.offset_x + width, y,
			game->minimap.border_color);
		y++;
	}
}

int	get_tile_color(t_game *game, char tile)
{
	if (tile == '1')
		return (game->minimap.wall_color);
	else if (tile == ' ')
		return (game->minimap.border_color);
	else
		return (game->minimap.floor_color);
}
