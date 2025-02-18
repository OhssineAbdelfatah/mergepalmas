#include "../includes/ps.h"

void	draw_disk(mlx_image_t *img, int x_c, int y_c, int radius, int color)
{
	int x;
	int y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				if ((x_c + x >= 0 && x_c + x < (int)img->width) && (y_c
						+ y < (int)img->height && y_c + y >= 0))
					mlx_put_pixel(img, x_c + x, y_c + y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_a_line2(t_main_s *var, int s_x, int s_y, int f_x, int f_y,
		int color, mlx_image_t *img)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(f_x - s_x);
	dy = abs(f_y - s_y);
	if (s_x < f_x)
		sx = 1;
	else
		sx = -1;
	if (s_y < f_y)
		sy = 1;
	else 
		sy = -1;
	err = dx - dy;
	while (1)
	{
		if (s_x == f_x && s_y == f_y)
			break ;
		if (s_x < 0 || s_y < 0)
			break ;
		if (var->window_height <= s_y || var->window_width <= s_x)
			break ;
		mlx_put_pixel(img, s_x, s_y, color);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			s_x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			s_y += sy;
		}
	}
}

// void	draw_a_line(t_main_s *var, int s_x, int s_y, int f_x, int f_y,
// 		int color, mlx_image_t *img)
// {
// 	int dx;
// 	int dy;
// 	float m;

// 	dx = f_x -s_x;
// 	dy = f_y - s_y;
// 	if (dx)
// 		m = dy / dx;
// 	(void)var;
// 	(void)img;
// 	// (void)line;
// };