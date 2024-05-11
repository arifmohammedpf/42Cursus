#include "fractol.h"

void	ft_error(void)
{
	ft_putstr("Invalid Arguments\n");
	exit (1);
}

void	initialize(t_data *img)
{
	img->width = 600;
	img->height = 600;
	img->base_color = 0x001642;
	img->fractol_type = 'j';
	img->zoom = 1;
	img->x_move = 0;
	img->y_move = 0;
	img->stop = 0;
	img->mlx = mlx_init();
	img->mlx_window = mlx_new_window(img->mlx, img->width, img->height, "Fractol");
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	validate(t_data *img, int argc, char **argv)
{
	if (argc == 3)
	{
		if (is_invalid_arg(argv[1]) || is_invalid_arg(argv[2]))
			ft_error();
		img->cx = ft_atof(argv[1]);
		if (img->cx < -2.0 || img->cx > 2.0)
			ft_error();
		img->cy = ft_atof(argv[2]);
		if (img->cy < -2.0 || img->cy > 2.0)
			ft_error();
		img->fractol_type = 'j';
	}
	else if (argc == 2 && ft_strcmp(argv[1], "1") == 0)
		img->fractol_type = 'm';
	else if (argc == 2 && ft_strcmp(argv[1], "2") == 0)
		img->fractol_type = 't';
	else
		ft_error();
}

int	main(int argc, char **argv)
{
	t_data	img;

	if (argc > 1 && argc <= 3)
	{
	  initialize(&img);
		validate(&img, argc, argv);
		show_fractol(&img);
		mlx_key_hook(img.mlx_window, key_control_hook, &img);
		mlx_mouse_hook(img.mlx_window, mouse_control_hook, &img);
		mlx_hook(img.mlx_window, 17, 0, close_hook, 0);
		mlx_loop(img.mlx);
	}
	else
		ft_error();
	return (0);
}
// // void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// // {
// // 	char	*dst;

// // 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// // 	*(unsigned int*)dst = color;
// // }

// int	key_hook(int keycode, t_data *vars)
// {
// 	printf("Hello from key_hook!\n");
// 	printf("Keycode: %d\n", keycode == KEY_ESC);
// 	return (0);
// }

// int main(int argc, char **argv)
// {
//   void	*mlx;
// 	void	*mlx_window;
// 	t_data	img;

// 	mlx = mlx_init();
// 	mlx_window = mlx_new_window(mlx, 600, 600, "Hello world!");
// 	img.img = mlx_new_image(mlx, 600, 600);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	my_mlx_pixel_put(&img, 150, 150, 0x0055FF);
// 	my_mlx_pixel_put(&img, 151, 151, 0x0055FF);
// 	my_mlx_pixel_put(&img, 152, 152, 0x0055FF);
// 	my_mlx_pixel_put(&img, 153, 153, 0x0055FF);
// 	my_mlx_pixel_put(&img, 154, 154, 0x0055FF);
// 	my_mlx_pixel_put(&img, 155, 155, 0x0055FF);
// 	my_mlx_pixel_put(&img, 156, 156, 0x0055FF);
// 	my_mlx_pixel_put(&img, 157, 157, 0x0055FF);
// 	my_mlx_pixel_put(&img, 158, 158, 0x0055FF);
// 	my_mlx_pixel_put(&img, 159, 159, 0x0055FF);
// 	my_mlx_pixel_put(&img, 160, 160, 0x0055FF);
// 	my_mlx_pixel_put(&img, 50, 50, 0x0055FF);
// 	my_mlx_pixel_put(&img, 51, 51, 0x0055FF);
// 	my_mlx_pixel_put(&img, 52, 52, 0x0055FF);
// 	my_mlx_pixel_put(&img, 53, 53, 0x0055FF);
// 	my_mlx_pixel_put(&img, 54, 54, 0x0055FF);
// 	my_mlx_pixel_put(&img, 55, 55, 0x0055FF);
// 	mlx_put_image_to_window(mlx, mlx_window, img.img, 150, 150);

// 	mlx_key_hook(mlx_window, key_hook, &img);

// 	mlx_loop(mlx);
// }