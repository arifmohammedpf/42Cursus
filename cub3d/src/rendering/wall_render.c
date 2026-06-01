/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:29:55 by rradin-m          #+#    #+#             */
/*   Updated: 2025/06/11 20:27:20 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_textured_wall(t_game *game, t_wall_data *wall,
		t_img_data *texture, int strip_id)
{
	double			texture_step;
	double			texture_pos;
	int				y;
	t_pixel_data	pixel;

	init_texture_params(wall, texture, &texture_step, &texture_pos);
	y = wall->wall_top;
	pixel.strip_id = strip_id;
	while (y <= wall->wall_bottom)
	{
		if (y >= 0 && y < SCREENHEIGHT && strip_id >= 0
			&& strip_id < SCREENWIDTH)
		{
			pixel.y = y;
			pixel.texture_pos = texture_pos;
			render_wall_pixel(game, wall, texture, pixel);
		}
		texture_pos += texture_step;
		y++;
	}
}

int	render_wall_strip(t_game *game, int strip_id)
{
	t_wall_data	wall;
	t_ray		*ray;
	t_img_data	*texture;

	ray = &game->raycast.rays[strip_id];
	if (ray->distance >= __DBL_MAX__ - 1)
		return (0);
	set_texture_number(&wall, ray);
	if (wall.texture_num < 0 || wall.texture_num >= 4)
		return (-1);
	texture = &game->textures[wall.texture_num];
	if (!texture->img || !texture->addr || texture->width == 0
		|| texture->height == 0)
		return (-1);
	calculate_wall_data(&wall, ray, texture);
	render_textured_wall(game, &wall, texture, strip_id);
	return (0);
}

int	render_3d_view(t_game *game)
{
	int	i;
	int	result;

	render_ceiling_and_floor(game);
	i = 0;
	while (i < game->raycast.num_rays)
	{
		result = render_wall_strip(game, i);
		if (result != 0)
			return (-1);
		i++;
	}
	return (0);
}
