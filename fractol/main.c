#include "fractol.h"

void	ft_error(void)
{
	ft_putstr("Invalid Arguments\n");
	ft_putstr("To Run Fractol: \n");
	ft_putstr("1. For Mandlebort => ./fractol 1 \n");
	ft_putstr("2. For Julia => ./fractol [-2 to 2] \n");
	ft_putstr("3. For Tricorn => ./fractol 2 \n");
	exit (1);
}

void	initialize(t_data *img)
{
	img->width = 600;
	img->height = 600;
	img->base_color = 0x001642;
	img->fractol_type = 'j';
	img->zoom = 1;
	img->is_motion = 0;
	img->mlx = mlx_init();
	img->mlx_window = mlx_new_window(img->mlx, img->width, img->height, "Fractol");
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
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
		mlx_hook(img.mlx_window, 17, 0, close_hook, 0);
		mlx_hook(img.mlx_window, 6, 1L < 6, mouse_motion_hook, &img);
		mlx_mouse_hook(img.mlx_window, mouse_control_hook, &img);
		mlx_key_hook(img.mlx_window, key_control_hook, &img);
		mlx_loop(img.mlx);
	}
	else
		ft_error();
	return (0);
}
