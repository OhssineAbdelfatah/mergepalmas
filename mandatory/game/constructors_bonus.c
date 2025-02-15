# include "../includes/ps.h"


t_obj *init_obj_p(t_main_s *var, t_player_infos *p_var)
{
    t_obj *res;

    if (var->bonus->nbr_obj == 0)
        return NULL;
    res = (t_obj *)malloc(sizeof(t_obj) * var->bonus->nbr_obj);
    if (!res)
        panic("malloc failed!\n");
    fill_obj(var, res, p_var);
    return res;
}

t_enemy *init_enemies_p(t_main_s *var, t_player_infos *p_var)
{
    t_enemy *res;

    if (var->bonus->nbr_enemies == 0)
        return NULL;
    res = (t_enemy *)malloc(sizeof(t_enemy) * var->bonus->nbr_enemies);
    if (!res)
        panic("malloc failed!\n");
    fill_enemy(var, res, p_var);
    return res;
}


int is_sorted(t_obj *obj,t_enemy *enemy, int max)
{
    int i = 0;
    if (obj)
    {
        while (i < max)
        {
            if (i + 1 < max)
                if (obj[i].distance < obj[i + 1].distance)
                    return 1;
            i++;
        }
        return 0;
    }
    while (i < max)
    {
        if (i + 1 < max)
            if (enemy[i].distance < enemy[i + 1].distance)
                return 1;
        i++;
    }

    return 0;
}


void swap_obj(t_obj *one, t_obj *two)
{
    t_obj tmp;

    tmp = *one;
    *one = *two;
    *two  = tmp;
}
void swap_enemy(t_enemy *one, t_enemy *two)
{
    t_enemy tmp;

    tmp = *one;
    *one = *two;
    *two  = tmp;
}

void adjust_rank(t_obj *obj, int max)
{
    int i = 0;
    while (is_sorted(obj, NULL, max))
    {
        i = 0;
        while (i < max)
        {
            if (i + 1 < max)
            {
                if (obj[i].distance < obj[i + 1].distance)
                    swap_obj(&obj[i], &obj[i + 1]);
            }
            i++;
        }
    }
}

void adjust_rank_enemies(t_enemy *enemy, int max)
{
    int i = 0;
    while (is_sorted(NULL, enemy, max))
    {
        i = 0;
        while (i < max)
        {
            if (i + 1 < max)
            {
                if (enemy[i].distance < enemy[i + 1].distance)
                    swap_enemy(&enemy[i], &enemy[i + 1]);
            }
            i++;
        }
    }
}

double calculate_obj_or_enemy_teta(t_player_infos *p_var, t_obj *obj, t_enemy *enemy)
{
    double teta;

    if (!enemy)
    {
        teta = p_var->rotation_angle + (p_var->fov / 2) - obj->vector_teta;
        if (p_var->rotation_angle < (M_PI / 2) && obj->vector_teta > (M_PI + (M_PI /2)))
            teta += (2 * M_PI);
        if (p_var->rotation_angle > (M_PI + (M_PI /2)) && obj->vector_teta < (M_PI / 2))
            teta -= (2 * M_PI);
        return (teta);
    }
    teta = p_var->rotation_angle + (p_var->fov / 2) - enemy->vector_teta;
    if (p_var->rotation_angle < (M_PI / 2) && enemy->vector_teta > (M_PI + (M_PI /2)))
        teta += (2 * M_PI);
    if (p_var->rotation_angle > (M_PI + (M_PI /2)) && enemy->vector_teta < (M_PI / 2))
        teta -= (2 * M_PI);
    return (teta);

}

void update_obj_data(t_main_s *var, t_player_infos *p_var, t_obj *obj,int nbr_obj)
{
    int i;

    i = 0;
    if (obj)
    {
        while (i < nbr_obj)
        {
            obj[i].distance = get_distance(p_var,obj[i].x, obj[i].y);
            obj[i].vector_x = p_var->y - obj[i].x;
            obj[i].vector_y = p_var->x - obj[i].y;
            obj[i].vector_teta = atan2(-obj[i].vector_y, obj[i].vector_x);
            obj[i].vector_teta = adjust_angle(obj[i].vector_teta  - (M_PI / 2));
            obj[i].obj_teta = calculate_obj_or_enemy_teta(p_var, &obj[i], NULL);
            obj[i].x_screen = obj[i].obj_teta * (1400 / p_var->fov);
            obj[i].y_screen = (var->window_height / 2) + var->p_infos->up_down_offset ;
            i++;
        }
        adjust_rank(obj, nbr_obj);
    } 
}


t_player_bonus *init_player_bonus(t_main_s *var, t_player_infos *p_var)
{
    t_player_bonus *res;

    res = (t_player_bonus *)malloc(sizeof(t_player_bonus));
    if (!res)
        panic("malloc failed!\n");
    p_var->jump_kneel = 0;
    p_var->look_up_down = 0;
    p_var->up_down_offset = 0;
    p_var->alive = true;
    p_var->health = 100;
    p_var->max_health = p_var->health;
    count_obj_enemi(var);
    res->enemy = init_enemies_p(var, p_var);
    res->obj = init_obj_p(var, p_var);
    return (res);
}



