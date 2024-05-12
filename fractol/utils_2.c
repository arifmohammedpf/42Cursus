#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); 
	*(unsigned int *) dst = color;
}

double	get_x0(t_data *img, int w)
{
	double	result;

	result = (w - img->width / 2) / (0.25 * img->zoom * img->width);
	return (result);
}

double	get_y0(t_data *img, int h)
{
	double	result;

	result = (h - img->height / 2) / (0.25 * img->zoom * img->height);
	return (result);
}
