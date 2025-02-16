/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:49:18 by ilaasri           #+#    #+#             */
/*   Updated: 2025/02/14 22:49:20 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORM_STRUCTS_H
#define NORM_STRUCTS_H

#include "game_structs.h"


typedef struct s_need_update t_need_update;
typedef struct s_render_obj t_render_obj;
typedef struct s_cast_rays t_cast_rays;
typedef struct s_shoot_the_rays  t_shoot_rays;
typedef struct s_fill_obj t_fill_obj;
typedef struct s_fill_enemy t_fill_enemy;


struct s_need_update
{
    int check;
    double move_steps;
    double new_y;
    double new_x;
    double tmp_angle;
};

struct s_render_obj
{
    int i;
    int obj_height;
    int obj_width;
    int x_start;
    int x_end;
    int  y_start;
    int  y_end;
    int color;
    int x_increment;
    int y_increment;
    int ray_to_inspect;
};



struct s_cast_rays
{
    t_x_and_y_d v_xy_door;
    t_x_and_y_d h_xy_door;
    t_x_and_y_d v_xy;
    t_x_and_y_d h_xy;
    double distance1;
    double distance2;
};


struct s_shoot_the_rays 
{
    double	ray_angle;
	int		i;
	double fov;
    double angle_to_start;
    double ray_angle_increment;  
};


struct s_fill_obj
{
    int x;
    int y;
    int i;
};

struct s_fill_enemy
{
    int x;
    int y;
    int i;
};

#endif
