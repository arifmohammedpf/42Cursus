/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:48:26 by rradin-m          #+#    #+#             */
/*   Updated: 2025/09/07 16:41:35 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		return (mlx_error_and_cleanup(game, "Failed to initialize MLX", 0));
	}
	game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, SCREENWIDTH, SCREENHEIGHT,
			"cub3D");
	if (!game->mlx.mlx_win)
		return (mlx_error_and_cleanup(game, "Failed to create window", 1));
	game->mlx.img = malloc(sizeof(t_img_data));
	if (!game->mlx.img)
		return (mlx_error_and_cleanup(game,
				"Failed to allocate image structure", 3));
	game->mlx.img->img = mlx_new_image(game->mlx.mlx, SCREENWIDTH,
			SCREENHEIGHT);
	if (!game->mlx.img->img)
		return (mlx_error_and_cleanup(game, "Failed to create MLX image", 4));
	game->mlx.img->addr = mlx_get_data_addr(game->mlx.img->img,
			&game->mlx.img->bits_per_pixel, &game->mlx.img->line_size,
			&game->mlx.img->endian);
	if (!game->mlx.img->addr)
		return (mlx_error_and_cleanup(game, "Failed to get image data address",
				4));
	return (0);
}

int	init_raycast(t_game *game)
{
	game->raycast.fov_angle = M_PI / 3;
	game->raycast.num_rays = SCREENWIDTH;
	game->raycast.rays = malloc(sizeof(t_ray) * game->raycast.num_rays);
	if (!game->raycast.rays)
		return (mlx_error_and_cleanup(game, "Failed to allocate rays", 4));
	return (0);
}
