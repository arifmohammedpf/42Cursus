#include "fractol.h"

int	close_hook(t_data *img)
{
	exit (0);
  return (0);
}

int	key_control_hook(int keycode, t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_window);
	if (keycode == 53 || keycode == 65307)
  {
    mlx_destroy_window(img->mlx, img->mlx_window);
    exit (0);
  }
	else if (keycode == 65436)
		img->base_color = 0x461178;
	else if (keycode == 65433)
		img->base_color = 0x961158;
	else if (keycode == 65435)
		img->base_color = 0x001642;
	else if (keycode == 65451)
    img->zoom *= 1.1;
  else if (keycode == 65453)
    img->zoom /= 1.1;
  show_fractol(img);
	return (0);
}

int	mouse_control_hook(int mouse_key_code, int x, int y, t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_window);
	if (mouse_key_code == 5)
		img->zoom *= 1.1;
	if (mouse_key_code == 4)
		img->zoom /= 1.1;
  show_fractol(img);
	return (0);
}
