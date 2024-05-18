#include "fractol.h"

int	close_hook(void)
{
	exit (0);
  return (0);
}

int	mouse_motion_hook(int x, int y, t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_window);
	if (img->is_motion == 0)
		img->cy = (x - img->width / 2)
			/ (0.25 * img->zoom * img->width);
	if (img->is_motion == 0)
		img->cx = (y - img->height / 2)
			/ (0.25 * img->zoom * img->height);
	show_fractol(img);
	return (0);
}

int	mouse_control_hook(int mouse_key_code, int x, int y, t_data *img)
{
	(void)x;
	(void)y;
	mlx_clear_window(img->mlx, img->mlx_window);
	if (mouse_key_code == 5) // Mouse keycode for wheel scroll up (Mac and Linux is same)
		img->zoom *= 1.1;
	else if (mouse_key_code == 4) // Mouse keycode for wheel scroll down (Mac and Linux is same)
		img->zoom /= 1.1;
  show_fractol(img);
	return (0);
}

int	key_control_hook(int keycode, t_data *img)
{
	mlx_clear_window(img->mlx, img->mlx_window);
	if (keycode == 53 || keycode == 65307) // Mac and Linux Keycode for Escape key
  {
    mlx_destroy_window(img->mlx, img->mlx_window);
    exit (0);
  }
	else if (keycode == 83 || keycode == 65436) // Mac and Linux Keycode for numpad key 1
		img->base_color = 0x461178;
	else if (keycode == 84 || keycode == 65433) // Mac and Linux Keycode for numpad key 2
		img->base_color = 0x961158;
	else if (keycode == 85 || keycode == 65435) // Mac and Linux Keycode for numpad key 3
		img->base_color = 0x001642;
	else if (keycode == 69 || keycode == 65451) // Mac and Linux Keycode for plus key in numpad
    img->zoom = img->zoom * 1.1;
  else if (keycode == 78 || keycode == 65453) // Mac and Linux Keycode for minus key in numbpad
    img->zoom = img->zoom / 1.1;
  else if (keycode == 49 || keycode == 32) // Mac and Linux Keycode for minus key in numbpad
    img->is_motion = 0;
  else if (keycode == 36 || keycode == 65293) // Mac and Linux Keycode for minus key in numbpad
    img->is_motion = 1;
  show_fractol(img);
	return (0);
}
