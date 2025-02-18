#include "../includes/ps.h"

void	paint_floor_celling(t_main_s *var)
{
	int		color;
	t_xy_i	start;
	t_xy_i	till;

	color = 0;
	//  color = create_trgb(var->parse->clr_c[0],var->parse->clr_c[1],
			// var->parse->clr_c[2], 255);
	till.x = (var->window_width);
	till.y = (var->window_height) / 2;
	start.x = 0;
	start.y = 0;
	paintit(var->img2, color, &start, &till);
	start.y = var->window_height / 2;
	// color = create_trgb(var->parse->clr_f[0],var->parse->clr_c[1],
			// var->parse->clr_c[2], 255);
	color = 0;
	paintit(var->img2, color, &start, &till);
}

void	first_part(t_main_s *var)
{
	t_work_of_art_part1	func;

	func.i = 0;
	func.p_x = (var->parse->pos->y_ver * square_len) + (square_len / 2);
	func.p_y = (var->parse->pos->x_hor * square_len) + (square_len / 2);
	var->p_infos = init_player_struct(var, var->parse->dir, func.p_x, func.p_y);
	func.c_x = (var->window_width / 2) - (var->bonus->crosshair_img->width / 2);
	func.c_y = (var->window_height / 2) - (var->bonus->crosshair_img->height
			/ 2);
	mlx_image_to_window(var->mlx, var->bonus->crosshair_img, func.c_x,
		func.c_y);
	while (func.i < 4)
	{
		func.x = var->window_width / 2 - (var->bonus->gun_img[func.i]->width
				/ 2);
		func.y = (var->window_height) - (var->bonus->gun_img[func.i]->height);
		mlx_image_to_window(var->mlx, var->bonus->gun_img[func.i], func.x,
			func.y);
		func.i++;
	}
	mlx_image_to_window(var->mlx, var->mini_map->img3, 10, 10);
}

void	work_of_art(t_main_s *var, int shoot)
{
	// paint_floor_celling(var);
	if (var->p_infos == NULL)
	{
		mlx_image_to_window(var->mlx, var->img2, 0, 0);
		first_part(var);
	}
	if (shoot)
	{
		free_rays(var);
		shoot_the_rays(var);
		draw_mini_map_42(var);
	}
	wall_rendering(var);
	update_obj_data(var, var->p_infos, var->p_infos->p_bonus->obj,
		var->bonus->nbr_obj);
	update_enemy_data(var, var->p_infos, var->p_infos->p_bonus->enemy,
		var->bonus->nbr_enemies);
	render_objects(var, var->p_infos->p_bonus);
	render_enemies(var, var->p_infos->p_bonus);
	draw_health_bar(var, var->p_infos->p_bonus->h_bar);
}
