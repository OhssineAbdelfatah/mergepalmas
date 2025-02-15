#include "../includes/ps.h"

int is_there_enemy(t_main_s *var, double x, double y)
{
    int new_enemy_x;
    int new_enemy_y;
    int i;

    i = var->bonus->nbr_enemies - 1;
    while (i >= 0)
    {
        new_enemy_x =(int)floor(var->p_infos->p_bonus->enemy[i].x / square_len);
        new_enemy_y = (int)floor(var->p_infos->p_bonus->enemy[i].y  / square_len);
        if (new_enemy_x == x && new_enemy_y == y)
        {
            if (var->p_infos->p_bonus->enemy[i].alive)
                return 1;
            else 
                return 2;

        }
        i--;
    }
    return 0;
}

int check_the_pixel(t_main_s *var, int x, int y)
{
    int enemy_there;
    int diff_x;
    int diff_y;
    int square;

    diff_x = (x - var->mini_map->p_x) * 2;
    diff_y = (y - var->mini_map->p_y) * 2;
    diff_x = ((int)floor(var->p_infos->y) + diff_x);
    diff_y = ((int)floor(var->p_infos->x) + diff_y);
    if (diff_x < 0 || diff_y < 0)
        return -1;
    diff_x /=  square_len; 
    diff_y /= square_len; 
    if (diff_y >= var->map_hight)
        return -1;
    if (diff_x >= (int)ft_strlen(var->map[diff_y]))
        return -1;
    square = var->map[diff_y][diff_x];
    if (square == '1')
        return 1;
    if (square == '\n' || square == 32)
        return -1;
    if (square == 'O')
        return -2;
    if (square == 'D')
        return -3;
    enemy_there = is_there_enemy(var, diff_x, diff_y); 
    if (enemy_there == 1)
        return (mlx_put_pixel(var->mini_map->img3, x, y, 0xD82020FF), -4);
    else if (enemy_there == 2)
        return(mlx_put_pixel(var->mini_map->img3, x, y, 0xCC6600FF),-5) ;

    return 0;
}

void draw_the_pixel_for_minimap(t_main_s *var, int x, int y)
{
    int check;
    
    check = check_the_pixel(var, x, y); 
    if (check == 0)
        mlx_put_pixel(var->mini_map->img3, x, y, 0xC0C0C0FF);
    else if (check == 1)
        mlx_put_pixel(var->mini_map->img3, x, y, 0x000000FF);
    else if (check == -1)
        mlx_put_pixel(var->mini_map->img3, x, y, 0x606060FF);
    else if (check == -2)
        mlx_put_pixel(var->mini_map->img3, x, y, 0x66CC00FF);
     else if (check == -3)
        mlx_put_pixel(var->mini_map->img3, x, y, 0x5EC4D4FF);
}

int draw_mini_map_42(t_main_s *var)
{
    int x, y;
    int new_x, new_y;

    x = 0;
    y = 0;
    while(x < var->mini_map->minimap_width)
    {
        while(y < var->mini_map->minimap_height)
        {
            draw_the_pixel_for_minimap(var, x, y);
            y++;
        }
        y = 0;
        x++;
    }
    new_x = var->mini_map->p_x + sin(var->p_infos->rotation_angle) * 30;
    new_y = var->mini_map->p_y + cos(var->p_infos->rotation_angle) * 30 ;
    draw_disk11(var->mini_map->img3, var->mini_map->p_x, var->mini_map->p_y , player_radius, 0x000000FF);
    draw_a_line2(var, var->mini_map->p_x , var->mini_map->p_y, new_x, new_y, 0x00F0FF,var->mini_map->img3);
    return 0;
}