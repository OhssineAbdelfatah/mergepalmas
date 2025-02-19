#include "../includes/ps.h"

void	free_rays(t_main_s *var)
{
	if (!var->p_infos->rays)
		return ;
	free(var->p_infos->rays);
	var->p_infos->rays = NULL;
}
