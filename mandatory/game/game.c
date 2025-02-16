# include "../includes/ps.h"

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
        mlx_image_to_window(var->mlx, var->bonus->gun_img[0], var->window_width / 2 - (var->bonus->gun_img[0]->width / 2), (var->window_height) - (var->bonus->gun_img[0]->height) );
        mlx_image_to_window(var->mlx, var->bonus->gun_img[1], var->window_width / 2 - (var->bonus->gun_img[1]->width / 2), (var->window_height) - (var->bonus->gun_img[1]->height) );
        mlx_image_to_window(var->mlx, var->bonus->gun_img[2], var->window_width / 2 - (var->bonus->gun_img[2]->width / 2), (var->window_height) - (var->bonus->gun_img[2]->height) );
        mlx_image_to_window(var->mlx, var->bonus->gun_img[3], var->window_width / 2 - (var->bonus->gun_img[3]->width / 2), (var->window_height) - (var->bonus->gun_img[3]->height) );
        mlx_image_to_window(var->mlx, var->mini_map->img3, 10, 10);
    }
    if (shoot)
    {
        free_rays(var);
        shoot_the_rays(var);
        draw_mini_map_42(var);
    }
    wall_rendering(var);
    update_obj_data(var, var->p_infos, var->p_infos->p_bonus->obj, var->bonus->nbr_obj);
    update_enemy_data(var, var->p_infos, var->p_infos->p_bonus->enemy, var->bonus->nbr_enemies);
    render_objects(var, var->p_infos->p_bonus);
    render_enemies(var, var->p_infos->p_bonus);
    draw_health_bar(var);
}

