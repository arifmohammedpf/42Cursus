#include "fractol.h"

static	void	algorithm(t_data *img, int height, int width)
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

void	show_mandelbrot(t_data *img)
{
	int	height;
	int	width;

	height = 0;
	while (height < img->height)
	{
		width = 0;
		while (width < img->width)
		{
			algorithm(img, height, width);
			width++;
		}
		height++;
	}
}