/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 23:50:14 by ilaasri           #+#    #+#             */
/*   Updated: 2025/02/14 23:50:16 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ps.h"

void	init_cst_horiz(t_casting *cst, t_main_s *var, int i)
{
	double	angle;

	angle = var->p_infos->rays[i].angle + (M_PI / 2.00);
	angle = adjust_angle(angle);
	cst->tan_angle = tan(angle);
	cst->xintersection = floor(var->p_infos->x / floor(square_len))
		* floor(square_len);
	if (var->p_infos->rays[i].facing_down)
		cst->xintersection += square_len;
	if (var->p_infos->rays[i].facing_right)
	{
		cst->yintersection = var->p_infos->y + ((var->p_infos->x
					- cst->xintersection) / cst->tan_angle);
	}
	else if (var->p_infos->rays[i].facing_left)
	{
		cst->yintersection = var->p_infos->y + ((var->p_infos->x
					- cst->xintersection) / cst->tan_angle);
	}
	cst->xsteps = square_len;
	cst->ysteps = cst->xsteps / cst->tan_angle;
	if (var->p_infos->rays[i].facing_down)
		cst->ysteps *= -1;
}

double	cast_horizontally(t_main_s *var, int i, t_x_and_y_d *xy,
		t_x_and_y_d *h_xy_door)
{
	double		up_down;
	t_casting	cst;

	init_cst_horiz(&cst, var, i);
	// if (0 == cst.tan_angle || cst.distance == -1)
	// 	return (-1);
	up_down = 1;
	if (var->p_infos->rays[i].facing_up)
		up_down = -1;
	while (cst.xintersection >= 0 && cst.yintersection >= 0)
	{
		if (hit_a_door(var, cst.xintersection + up_down, cst.yintersection, i)
			&& !h_xy_door->hit_a_door)
		{
			h_xy_door->hit_a_door = true;
			h_xy_door->y = cst.xintersection;
			h_xy_door->x = cst.yintersection;
			h_xy_door->distance = sqrt(pow((cst.xintersection
							- var->p_infos->x), 2) + pow((cst.yintersection
							- var->p_infos->y), 2));
		}
		if (hit_a_wall(var, cst.xintersection + up_down, cst.yintersection, i))
		{
			xy->y = cst.xintersection;
			xy->x = cst.yintersection;
			break ;
		}
		cst.xintersection += (cst.xsteps * up_down);
		cst.yintersection += cst.ysteps;
	}
	cst.distance = sqrt(pow((cst.xintersection - var->p_infos->x), 2)
			+ pow((cst.yintersection - var->p_infos->y), 2));
	return (cst.distance);
}

void	init_cst_vert(t_casting *cst, t_main_s *var, int i)
{
	double	left_right;
	double	angle;

	angle = var->p_infos->rays[i].angle - (M_PI / 2);
	angle = adjust_angle(angle);
	cst->tan_angle = tan(angle);
	left_right = 1;
	if (var->p_infos->rays[i].facing_left)
		left_right = -1;
	cst->yintersection = floor(var->p_infos->y / square_len) * square_len;
	if (left_right == 1)
		cst->yintersection += square_len;
	if (var->p_infos->rays[i].facing_up)
		cst->xintersection = var->p_infos->x - ((cst->yintersection
					- var->p_infos->y) * cst->tan_angle);
	else
		cst->xintersection = var->p_infos->x - ((cst->yintersection
					- var->p_infos->y) * cst->tan_angle);
	cst->ysteps = square_len;
	cst->xsteps = cst->ysteps * cst->tan_angle;
	if (var->p_infos->rays[i].facing_left)
		cst->ysteps *= -1;
	else
		cst->xsteps *= -1;
}

double	cast_vertically(t_main_s *var, int i, t_x_and_y_d *xy,
		t_x_and_y_d *v_xy_door)
{
	t_casting	cst;
	double		left_right;

	init_cst_vert(&cst, var, i);
	left_right = 1;
	if (var->p_infos->rays[i].facing_left)
		left_right = -1;
	while (cst.xintersection >= 0.00 && cst.yintersection >= 0.00)
	{
		if (hit_a_door(var, cst.xintersection, cst.yintersection + left_right,
				i) && !v_xy_door->hit_a_door)
		{
			v_xy_door->hit_a_door = true;
			v_xy_door->y = cst.xintersection;
			v_xy_door->x = cst.yintersection;
			v_xy_door->distance = sqrt(pow((cst.xintersection
							- var->p_infos->x), 2) + pow((cst.yintersection
							- var->p_infos->y), 2));
		}
		if (hit_a_wall(var, cst.xintersection, cst.yintersection + left_right,
				i))
		{
			xy->y = cst.xintersection;
			xy->x = cst.yintersection;
			break ;
		}
		cst.xintersection += cst.xsteps;
		cst.yintersection += cst.ysteps;
	}
	cst.distance = sqrt(pow((cst.xintersection - var->p_infos->x), 2)
			+ pow(cst.yintersection - var->p_infos->y, 2));
	return (cst.distance);
}
