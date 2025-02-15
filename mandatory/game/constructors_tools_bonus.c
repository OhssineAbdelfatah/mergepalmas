# include "../includes/ps.h"

double get_distance(t_player_infos *p_var, double x, double y)
{
    double distance;
    distance = sqrt(pow((p_var->y - x), 2) +  pow((p_var->x - y), 2));
    return (distance);
}

void fill_obj(t_main_s *var, t_obj *obj, t_player_infos *p_var)
{
    int x;
    int y;
    int i;

    x = 0;
    y = 0;
    i = 0;
    while (var->map[y])
    {   
        x = 0;
        while (var->map[y][x])
        {
            if (var->map[y][x] == 'O')
            {
                obj[i].visible = false;
                obj[i].x = (double)(x * square_len) + (square_len / 2);
                obj[i].y = (double)(y * square_len) + (square_len / 2);
                obj[i].x_screen = 0;
                obj[i].y_screen = 0;
                obj[i].obj_height = 0;
                obj[i].obj_width = 0;
                obj[i].obj_teta = 0;
                obj[i].vector_teta = 0;
                obj[i].vector_x = 0;
                obj[i].vector_y = 0;
                obj[i].distance = get_distance(p_var,x, y);
                i++;
            }
            x ++;
        }
        y++;
    }
}

void fill_enemy(t_main_s *var, t_enemy *enemy, t_player_infos *p_var)
{
    int x;
    int y;
    int i;

    x = 0;
    y = 0;
    i = 0;
    while (var->map[y])
    {   
        x = 0;
        while (var->map[y][x])
        {
            if (var->map[y][x] == 'e')
            {
                enemy[i].alive = true;
                enemy[i].x = (double)(x * square_len) + (square_len / 2);
                enemy[i].y = (double)(y * square_len) + (square_len / 2);
                enemy[i].x_screen = 0;
                enemy[i].y_screen = 0;
                enemy[i].enemy_height = 0;
                enemy[i].enemy_width = 0;
                enemy[i].enemy_teta = 0;
                enemy[i].vector_teta = 0;
                enemy[i].vector_x = 0;
                enemy[i].vector_y = 0;
                enemy[i].distance = get_distance(p_var,x, y);
                i++;
            }
            x ++;
        }
        y++;
    }
}
