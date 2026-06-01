/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:29:43 by rradin-m          #+#    #+#             */
/*   Updated: 2025/07/14 15:35:31 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREENWIDTH || y < 0 || y >= SCREENHEIGHT)
		return ;
	dst = data->addr + (y * data->line_size + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_pixel(t_img_data *texture, int x, int y)
{
	int	*data;

	if (!texture || !texture->addr)
		return (0);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	data = (int *)texture->addr;
	return (data[y * (texture->line_size / 4) + x]);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
