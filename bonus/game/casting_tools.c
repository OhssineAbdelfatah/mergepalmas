/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 23:49:36 by ilaasri           #+#    #+#             */
/*   Updated: 2025/02/14 23:49:37 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ps.h"

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

int	hit_a_door(t_main_s *var, double xintersection, double yintersection, int i)
{
	int	x;
	int	y;

	x = (int)floor(xintersection / square_len);
	y = (int)floor(yintersection / square_len);
	if (y < 0 || x < 0 || x >= var->map_hight
		|| y > (int)ft_strlen(var->map[x]))
		return (0);
	if (var->map[x][y] == 'D')
		return (1);
	(void)i;
	return (0);
}

int	hit_a_wall(t_main_s *var, double xintersection, double yintersection, int i)
{
	int	x;
	int	y;

	x = (int)floor(xintersection / square_len);
	y = (int)floor(yintersection / square_len);
	if (y < 0 || x < 0 || x >= var->map_hight
		|| y > (int)ft_strlen(var->map[x]))
		return (1);
	if (var->map[x][y] == '1')
		return (1);
	(void)i;
	return (0);
}
