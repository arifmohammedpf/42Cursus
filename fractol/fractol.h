
# ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx/mlx.h"

typedef struct s_data
{
	void		*mlx;
	void		*mlx_window;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			is_motion;
	char		fractol_type;
	int			base_color;
	int			iteration;
	int			max_iteration;
	double	xtemp;
	double	cx;
	double	cy;
	double	zoom;
	double	x_axis_move;
	double	y_axis_move;
}	t_data;

void	initialize(t_data *img);
void	validate(t_data *img, int ac, char **av);
void	show_fractol(t_data *img);

double	get_x0(t_data *img, int w);
double	get_y0(t_data *img, int h);
int		is_invalid_arg(const char *str1);
void	ft_error(void);
int		close_hook();
void	ft_putstr(char *str);
int		ft_strcmp(const char *s1, const char *s2);
double	ft_atof(const char *str);

void	my_mlx_pixel_put(t_data *data, int x, int y, int colour);
int		mouse_control_hook(int mouse_key_code, int x, int y, t_data *img);
int		key_control_hook(int keycode, t_data *img);
int		mouse_motion_hook(int x, int y, t_data *img);

#endif
