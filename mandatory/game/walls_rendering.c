#include "../includes/ps.h"

t_text *which_texture(t_ray_info* ray, t_text** texture)
{
    if(ray->wall_dir ==  'W')
        return texture[0];
    if(ray->wall_dir ==  'E')
        return texture[1];
    if(ray->wall_dir ==  'S')
        return texture[2];
    if(ray->wall_dir ==  'N')
        return texture[3];
    return NULL;
}

int	gettt_rgba2(uint8_t *color, int trans)
{
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | trans);
}

void draw_rectangle(t_main_s *var, t_text* text,int x, int top , int buttom, int x_img, int color, int transparency,int ray_nbr)
{
    int j; 
    int y_img;
    j = top;

    while (j < buttom)
    {
        if (j >= 0 && j < var->window_height) // window hieght
        {
            y_img = calc_y_img(j - top, buttom - top, text->hieght);
            color = text->pixels[y_img][x_img];
            mlx_put_pixel(var->img2, x , j , color);
        }
        j++;
    }
    (void)transparency;
    (void)ray_nbr;
    return ;
}

double adjust_distance(t_main_s *var, int i)
{
    double teta_angle;
    double adjusted_distance ;

    teta_angle = var->p_infos->rays[i].angle - var->p_infos->rays[var->p_infos->nbr_rays / 2].angle;
    if (teta_angle < 0)
        teta_angle *= -1;
    adjusted_distance = cos(teta_angle) * var->p_infos->rays[i].distance;
    return adjusted_distance; 
}





int get_transparency(double distance)
{
    // static int ss;
    int i, distance2;
    i = 0;
    distance2 = (int)floor(distance);
    while (i < distance2)
        i++;
    i /= 5;
    if (i > 255)
        i = 255;
    return (255 - i);
}






void    wall_rendering(t_main_s *var)
{
    t_walls *walls;
    t_text *texture;
    double adjusted_distance;
    int color = 0 ;
    int transparency;
    int top;
    int buttom;
    int x_img;
    int i;
    int j;
    static double offset = 1;

    i = var->p_infos->nbr_rays-1;
    j = 0;
    walls = init_walls(var);
    if (offset >= 0 && var->p_infos->rays[699].bonus_rays->door->distance < 128 && var->p_infos->rays[699].bonus_rays->door->distance > 0)
        offset -= 0.1;
    else if( offset < 1 && var->p_infos->rays[699].bonus_rays->door->distance > 128 &&  var->p_infos->rays[699].bonus_rays->door->distance > 0) 
        offset += 0.1;
    while (i >= 0)
    {
        texture = which_texture(var->p_infos->rays+i, var->text);
        adjusted_distance = adjust_distance(var, i);
        if (adjusted_distance == 0)
            adjusted_distance = 0.5;
        walls->wall_hight = (square_len / adjusted_distance) * walls->distance_prj_plane;
        top = (((var->window_height) / 2) - (walls->wall_hight / 2)) + var->p_infos->up_down_offset;
        buttom = top + walls->wall_hight;
        x_img = calc_x_img(var->p_infos->rays[i].horzt_or_vert, var->p_infos->rays + i, square_len, texture->width);
        transparency = get_transparency(adjusted_distance);
        render_sky(var, j, top, i);
        draw_rectangle(var,texture, j, top, buttom, x_img, color, transparency, i);
        draw_floor(var, j, buttom, i);
        if(is_there_door(var->p_infos->rays[i].bonus_rays, var, i))
            draw_door(var, walls,i,j, offset);

        i--;
        j++;
    }
    free(walls);
}
