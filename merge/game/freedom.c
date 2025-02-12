#include "../includes/ps.h"


void free_rays_bonus(t_ray_info *var)
{
    if (var->bonus_rays)
    {
        if (var->bonus_rays->door)
        {
            free(var->bonus_rays->door);
            var->bonus_rays->door = NULL;
        }
        if (var->bonus_rays->enemi)
            free(var->bonus_rays->enemi);
        if (var->bonus_rays->obj)
            free(var->bonus_rays->obj);
    }
}

void free_rays(t_main_s *var)
{
    int i;
    i = 0;
    while (i < var->p_infos->nbr_rays)
    {
        free_rays_bonus(&var->p_infos->rays[i]);
        free(var->p_infos->rays[i].bonus_rays);
        i++;
    }
    free(var->p_infos->rays);
}