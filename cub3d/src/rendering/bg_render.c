/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:29:34 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/12 17:49:56 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	render_ceiling(int *img_data, int line_length, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			img_data[y * line_length + x] = ceiling_color;
			x++;
		}
		y++;
	}
}

static void	render_floor(int *img_data, int line_length, int floor_color)
{
	int	x;
	int	y;

	y = SCREENHEIGHT / 2;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			img_data[y * line_length + x] = floor_color;
			x++;
		}
		y++;
	}
}

void	render_ceiling_and_floor(t_game *game)
{
	int	ceiling_color;
	int	floor_color;
	int	*img_data;
	int	line_length;

	if (!game->mlx.img || !game->mlx.img->addr)
		return ;
	ceiling_color = create_rgb(game->map_data.roof.r, game->map_data.roof.g,
			game->map_data.roof.b);
	floor_color = create_rgb(game->map_data.floor.r, game->map_data.floor.g,
			game->map_data.floor.b);
	img_data = (int *)game->mlx.img->addr;
	line_length = game->mlx.img->line_size / 4;
	render_ceiling(img_data, line_length, ceiling_color);
	render_floor(img_data, line_length, floor_color);
}
