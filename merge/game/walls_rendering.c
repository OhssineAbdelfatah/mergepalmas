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
    double which_distance ;
    double teta_angle;
    double adjusted_distance ;

    which_distance = var->p_infos->rays[i].distance;
    
    teta_angle = var->p_infos->rays[i].angle - var->p_infos->rays[var->p_infos->nbr_rays / 2].angle;
    if (teta_angle < 0)
        teta_angle *= -1;
    adjusted_distance = cos(teta_angle) * which_distance;
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


int get_color_of_floor(t_main_s *var, double x, double y)
{
    int color;
    double x_offset;
    double y_offset;

    int new_x, new_y;

    x_offset = (double)x /square_len;
    y_offset = (double)y / square_len;

    x_offset = x_offset - floor(x_offset);
    y_offset = y_offset - floor(y_offset);

    new_x = (double)var->bonus->floor_text->width * x_offset;
    new_y = (double)var->bonus->floor_text->hieght * y_offset;

    color = var->bonus->floor_text->pixels[(int)floor(new_y)][(int)floor(new_x)];
    return color;
}

int get_color_for_floor(t_main_s *var, int x, int y, int nbr_ray)
{
    int color;
    double beta,r,  straight_line_dis, origin_line_distance, floor_x, floor_y;

    beta = var->p_infos->rays[nbr_ray].angle - var->p_infos->rotation_angle;
    beta = adjust_angle(beta);
    r = y -  (var->window_height / 2);
    straight_line_dis = ((square_len / 2) / r) * var->p_infos->walls->distance_prj_plane;
    origin_line_distance = straight_line_dis / cos(beta);
    floor_x = var->p_infos->x + (cos(var->p_infos->rays[nbr_ray].angle) * origin_line_distance);
    floor_y = var->p_infos->y - (sin(var->p_infos->rays[nbr_ray].angle) * origin_line_distance) ;

    color = get_color_of_floor(var, floor_x, floor_y);
    (void)x;
    // (void)i;
    return color;
}

void draw_floor(t_main_s *var, int x, int y, int nbr_ray)
{
    int color;

    while (y < var->window_height)
    {
        color = get_color_for_floor(var, x, y, nbr_ray);
        if (color)
            mlx_put_pixel(var->img2, x, y, color);
        y++;
    }
}



int get_sky_color (t_main_s *var, int y, int nbr_ray)
{
    int color;
    int x_sky, y_sky;

    y_sky =  (int)floor( (double)var->bonus->sky_text->hieght *  ((double)y /  (double)(var->window_height / 2)));

    x_sky = (int)floor(var->p_infos->rays[nbr_ray].angle * ((double)var->bonus->sky_text->width / (2 * M_PI))); 

    color = var->bonus->sky_text->pixels[y_sky][x_sky];
    return color;
}

void render_sky(t_main_s *var, int x, int y_end, int nbr_ray)
{
    int color;
    int y;

    y = 0;
    while (y < y_end)
    {
        color = get_sky_color(var, y, nbr_ray);
        if (color)
            mlx_put_pixel(var->img2, x, y, color);
        y++;
    }
}

void init_calc(t_calc_img* calc,double door_h, double img_w, double img_door_w )
{
    calc->door_h = door_h;
    calc->img_door_w = img_door_w;
    calc->img_w = img_w;
    return ;
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
        top = ((var->window_height) / 2) - (walls->wall_hight / 2);
        buttom = ((var->window_height) / 2) + (walls->wall_hight / 2);
        x_img = calc_x_img(var->p_infos->rays[i].horzt_or_vert, var->p_infos->rays + i, square_len, texture->width);
        transparency = get_transparency(adjusted_distance);
        // render_sky(var, j, top, i);
        draw_rectangle(var,texture, j, top, buttom, x_img, color, transparency, i);
        if(is_there_door(var->p_infos->rays[i].bonus_rays, var, i))
            draw_door(var, walls,i,j, offset);
        // draw_floor(var, j, x, i);

        i--;
        j++;
    }
    (void)x_img;
    free(walls);
}