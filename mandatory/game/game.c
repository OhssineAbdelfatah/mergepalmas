# include "../includes/ps.h"

<<<<<<< HEAD
=======

>>>>>>> 4b38982e2d627d87528018ae12d97d5b63d03de7
double calcul_obj_height(t_main_s *var, int i)
{
    double height;

    height = ((square_len ) / var->p_infos->rays[i].bonus_rays->obj->distance) * var->p_infos->walls->distance_prj_plane;
    return height;
}


double calc_obj_width(t_main_s *var)
{
    int i,first, last;
    double width;

    width = 0;
    i = var->p_infos->nbr_rays - 1;
    first = -1;
    last = -1;
    while (i >= 0)
    {
        if (var->p_infos->rays[i].bonus_rays->hit_an_obj == true)
        {
            if (first == -1)
                first = i;
            if ( i - 1 >= 0 && var->p_infos->rays[i - 1].bonus_rays->hit_an_obj == false)
                last = i ;

        }
        i--;
    }
    if (first != -1 && last == -1)
        last = 0;
    if (last != -1 && first != -1)
        width = first - last;
    return width;
}


int get_color_obj(t_main_s *var, int obj_height, int obj_width, int x, int y)
{
    int color;
    double x_offset;
    double y_offset;

    int new_x, new_y;

    x_offset = (double)x / (double)obj_width;
    y_offset = (double)y / (double)obj_height;

    new_x = (double)var->bonus->pillar_img->width * x_offset;
    new_y = (double)var->bonus->pillar_img->hieght * y_offset;

    color = var->bonus->pillar_img->pixels[(int)floor(new_y)][(int)floor(new_x)];
    return color;
}


void paint_floor_celling(t_main_s *var)
{
    int color;
    t_xy_i start;
    t_xy_i till;
    
    color = 0;
    //  color = create_trgb(var->parse->clr_c[0],var->parse->clr_c[1], var->parse->clr_c[2], 255); 
    till.x = (var->window_width);
    till.y = (var->window_height) /2;
    start.x = 0;
    start.y = 0;
    paintit(var->img2,color,  &start, &till );
    start.y = var->window_height / 2;
    // color = create_trgb(var->parse->clr_f[0],var->parse->clr_c[1], var->parse->clr_c[2], 255); 
    color = 0;
    paintit(var->img2, color, &start, &till);
}

void work_of_art(t_main_s *var, int shoot)
{  
    // paint_floor_celling(var);
    if (var->p_infos == NULL)
    {
        var->p_infos=  init_player_struct(var , var->parse->dir, ((var->parse->pos->y_ver * square_len) + (square_len / 2)), ((var->parse->pos->x_hor * square_len) + (square_len / 2)));
        mlx_image_to_window(var->mlx, var->img2, 0, 0);
        mlx_image_to_window(var->mlx, var->bonus->crosshair_img, (var->window_width / 2) - (var->bonus->crosshair_img->width / 2) , (var->window_height / 2) - (var->bonus->crosshair_img->height / 2));
        mlx_image_to_window(var->mlx, var->bonus->gun_in_hands_img[0], var->window_width / 2 - (var->bonus->gun_in_hands_img[0]->width / 2), (var->window_height) - (var->bonus->gun_in_hands_img[0]->height) );
        mlx_image_to_window(var->mlx, var->bonus->gun_in_hands_img[1], var->window_width / 2 - (var->bonus->gun_in_hands_img[1]->width / 2), (var->window_height) - (var->bonus->gun_in_hands_img[1]->height) );
        mlx_image_to_window(var->mlx, var->bonus->gun_in_hands_img[2], var->window_width / 2 - (var->bonus->gun_in_hands_img[2]->width / 2), (var->window_height) - (var->bonus->gun_in_hands_img[2]->height) );
        mlx_image_to_window(var->mlx, var->bonus->gun_in_hands_img[3], var->window_width / 2 - (var->bonus->gun_in_hands_img[3]->width / 2), (var->window_height) - (var->bonus->gun_in_hands_img[3]->height) );
        mlx_image_to_window(var->mlx, var->mini_map->img3, 10, 10);
    }
    if (shoot)
    {
        free_rays(var);
        shoot_the_rays(var);
    }
    draw_mini_map_42(var);
    wall_rendering(var);
    update_obj_data(var, var->p_infos, var->p_infos->p_bonus->obj, var->bonus->nbr_obj);
    update_enemy_data(var, var->p_infos, var->p_infos->p_bonus->enemy, var->bonus->nbr_enemies);
    render_objects(var, var->p_infos->p_bonus);
    render_enemies(var, var->p_infos->p_bonus);
    draw_health_bar(var);
}

