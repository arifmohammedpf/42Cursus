#include "fractol.h"

static void	show_mandelbrot(t_data *img, int height, int width)
{
	double	x;
	double	y;
	double	x0;
	double	y0;

	x = 0.0;
	y = 0.0;
	img->xtemp = 0.0;
	img->iteration = 0;
	img->max_iteration = 40;
	img->offset = 0.05;
	while (x * x + y * y <= 2 * 2 && img->iteration < img->max_iteration)
	{
    x0 = get_x0(img, width);
    y0 = get_y0(img, height);
		img->xtemp = x * x - y * y + x0;
		y = 2.0 * x * y + y0;
		x = img->xtemp;
		img->iteration += 1;
	}
	if (img->iteration == img->max_iteration)
		my_mlx_pixel_put(img, width, height, img->base_color);
	else
		my_mlx_pixel_put(img, width, height, img->base_color * img->iteration);
	width++;
}

static	void	show_julia(t_data *img, int height, int width)
{
	double	zx;
	double	zy;

	zx = get_x0(img, width);
	zy = get_y0(img, height);
	img->xtemp = 0.0;
	img->iteration = 0;
	img->max_iteration = 500;
	while (zx * zx + zy * zy < 2 * 2 && img->iteration < img->max_iteration)
	{
		img->xtemp = zx * zx - zy * zy;
		zy = 2.0 * zx * zy + img->cy;
		zx = img->xtemp + img->cx;
		img->iteration += 1;
	}
	if (img->iteration == img->max_iteration)
		my_mlx_pixel_put(img, width, height, img->base_color);
	else
		my_mlx_pixel_put(img, width, height, img->base_color * img->iteration);
	width++;
}

static	void	show_tricorn(t_data *img, int height, int width)
{
	double	x;
	double	y;

	x = 0.0;
	y = 0.0;
	img->xtemp = 0.0;
	img->iteration = 0;
	img->max_iteration = 200;
	img->offset = 0.05;
	while (x * x + y * y <= 4 && img->iteration < img->max_iteration)
	{
		img->xtemp = x * x - y * y + get_x0(img, width);
		y = -2.0 * x * y + get_y0(img, height);
		x = img->xtemp;
		img->iteration += 1;
	}
	if (img->iteration == img->max_iteration)
		my_mlx_pixel_put(img, width, height, img->base_color);
	else
		my_mlx_pixel_put(img, width, height, img->base_color * img->iteration);
	width++;
}

void	show_fractol(t_data *img)
{
	int	height;
	int	width;

	height = 0;
	while (height < img->height)
	{
		width = 0;
		while (width < img->width)
		{
			if (img->fractol_type == 'm')
				show_mandelbrot(img, height, width);
			else if (img->fractol_type == 'j')
				show_julia(img, height, width);
			else if (img->fractol_type == 't')
				show_tricorn(img, height, width);
			width++;
		}
		height++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_window, img->img, 0, 0);
}
