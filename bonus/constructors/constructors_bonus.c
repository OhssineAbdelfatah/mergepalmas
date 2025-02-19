#include "../includes/ps.h"

t_ray_hit_door	*init_door(void)
{
	t_ray_hit_door	*ret;

	ret = (t_ray_hit_door *)malloc(sizeof(t_ray_hit_door));
	if (!ret)
		panic("malloc failed !\n");
	ret->distance = 0;
	ret->from = 0;
	ret->x_intersection = 0;
	ret->y_intersection = 0;
	return (ret);
}

t_rays_bonus	*init_bonus_rays(void)
{
	t_rays_bonus	*ret;

	ret = (t_rays_bonus *)malloc(sizeof(t_rays_bonus));
	if (!ret)
		panic("malloc failed !\n");
	ret->hit_a_door = false;
	ret->door = init_door();
	return (ret);
}

t_mini_map	*init_mini_map(void *mlx, int width, int height)
{
	t_mini_map	*var;

	var = malloc(sizeof(t_mini_map));
	if (!var)
		panic("malloc faild !\n");
	var->mini_square_len = 32;
	var->minimap_height = 32 * 7;
	var->minimap_width = 32 * 9;
	var->p_y = var->minimap_height / 2;
	var->p_x = var->minimap_width / 2;
	var->img3 = mlx_new_image(mlx, var->minimap_width, var->minimap_height);
	(void)height;
	(void)width;
	return (var);
}

void	resizing_img_bonus(t_main_s *main, t_bonus *var)
{
	mlx_resize_image(var->crosshair_img, main->window_width / 14,
		main->window_height / 8);
	mlx_resize_image(var->gun_img[0], main->window_width - (main->window_width
			/ 3), main->window_height - (main->window_height / 3));
	mlx_resize_image(var->gun_img[1], main->window_width - (main->window_width
			/ 3), main->window_height - (main->window_height / 3));
	mlx_resize_image(var->gun_img[2], main->window_width - (main->window_width
			/ 3), main->window_height - (main->window_height / 3));
	mlx_resize_image(var->gun_img[3], main->window_width - (main->window_width
			/ 3), main->window_height - (main->window_height / 3));
}

mlx_image_t	*get_mlximg(t_main_s *var, char *path)
{
	mlx_texture_t	*tmp;
	mlx_image_t		*ret;

	tmp = safe_load(path);
	ret = mlx_texture_to_image(var->mlx, tmp);
	mlx_delete_texture(tmp);
	if (!ret)
		panic("mlx_texture_to_image failed !\n");
	return (ret);
}

t_bonus	*init_bonus(t_main_s *main)
{
	t_bonus	*var;

	var = (t_bonus *)malloc(sizeof(t_bonus));
	if (!var)
		panic("malloc faild! \n");
	var->enemy_text = safe_img_cnv("./assets/textures/AGAHA1.png");
	var->dead_enemy_text = safe_img_cnv("./assets/textures/AGAHL0.png");
	var->door = safe_img_cnv("./assets/textures/doortile.png");
	var->floor_text = safe_img_cnv("./assets/floor/Brick/brick1.png");
	var->sky_text = safe_img_cnv("./assets/sky/FuzzySky/Sunset.png");
	var->obj_img = safe_img_cnv("./assets/textures/EHEDC0.png");
	var->gun_img[0] = get_mlximg(main, "./assets/textures/RGLGD0.png");
	var->gun_img[1] = get_mlximg(main, "./assets/textures/RGLFA0.png");
	var->gun_img[2] = get_mlximg(main, "./assets/textures/RGLFB0.png");
	var->gun_img[3] = get_mlximg(main, "./assets/textures/RGLFC0.png");
	var->crosshair_img = get_mlximg(main, "./assets/textures/techno1.png");
	resizing_img_bonus(main, var);
	var->gun_img[1]->enabled = false;
	var->gun_img[2]->enabled = false;
	var->gun_img[3]->enabled = false;
	var->mouse_x = (main->window_width) / 2;
	var->mouse_y = (main->window_height) / 2;
	var->nbr_enemies = 0;
	var->nbr_obj = 0;
	return (var);
}

t_obj	*init_obj_p(t_main_s *var, t_player_infos *p_var)
{
	t_obj	*res;

	if (var->bonus->nbr_obj == 0)
		return (NULL);
	res = (t_obj *)malloc(sizeof(t_obj) * var->bonus->nbr_obj);
	if (!res)
		panic("malloc failed!\n");
	fill_obj(var, res, p_var);
	return (res);
}

t_enemy	*init_enemies_p(t_main_s *var, t_player_infos *p_var)
{
	t_enemy	*res;

	if (var->bonus->nbr_enemies == 0)
		return (NULL);
	res = (t_enemy *)malloc(sizeof(t_enemy) * var->bonus->nbr_enemies);
	if (!res)
		panic("malloc failed!\n");
	fill_enemy(var, res, p_var);
	return (res);
}

int	is_sorted(t_obj *obj, t_enemy *enemy, int max)
{
	int	i;

	i = 0;
	if (obj)
	{
		while (i < max)
		{
			if (i + 1 < max)
				if (obj[i].distance < obj[i + 1].distance)
					return (1);
			i++;
		}
		return (0);
	}
	while (i < max)
	{
		if (i + 1 < max)
			if (enemy[i].distance < enemy[i + 1].distance)
				return (1);
		i++;
	}
	return (0);
}

void	swap_obj(t_obj *one, t_obj *two)
{
	t_obj	tmp;

	tmp = *one;
	*one = *two;
	*two = tmp;
}

void	swap_enemy(t_enemy *one, t_enemy *two)
{
	t_enemy	tmp;

	tmp = *one;
	*one = *two;
	*two = tmp;
}

void	adjust_rank(t_obj *obj, int max)
{
	int	i;

	i = 0;
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

void	adjust_rank_enemies(t_enemy *enemy, int max)
{
	int	i;

	i = 0;
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

double	calculate_obj_or_enemy_teta(t_player_infos *p_var, t_obj *obj,
		t_enemy *enemy)
{
	double	teta;

	if (!enemy)
	{
		teta = p_var->rotation_angle + (p_var->fov / 2) - obj->vector_teta;
		if (p_var->rotation_angle < (M_PI / 2) && obj->vector_teta > (M_PI
				+ (M_PI / 2)))
			teta += (2 * M_PI);
		if (p_var->rotation_angle > (M_PI + (M_PI / 2))
			&& obj->vector_teta < (M_PI / 2))
			teta -= (2 * M_PI);
		return (teta);
	}
	teta = p_var->rotation_angle + (p_var->fov / 2) - enemy->vector_teta;
	if (p_var->rotation_angle < (M_PI / 2) && enemy->vector_teta > (M_PI + (M_PI
				/ 2)))
		teta += (2 * M_PI);
	if (p_var->rotation_angle > (M_PI + (M_PI / 2))
		&& enemy->vector_teta < (M_PI / 2))
		teta -= (2 * M_PI);
	return (teta);
}

void	update_obj_data(t_main_s *var, t_player_infos *p_var, t_obj *obj,
		int nbr_obj)
{
	int	i;

	i = 0;
	if (obj)
	{
		while (i < nbr_obj)
		{
			obj[i].distance = get_distance(p_var, obj[i].x, obj[i].y);
			obj[i].vector_x = p_var->y - obj[i].x;
			obj[i].vector_y = p_var->x - obj[i].y;
			obj[i].vector_teta = atan2(-obj[i].vector_y, obj[i].vector_x);
			obj[i].vector_teta = adjust_angle(obj[i].vector_teta - (M_PI / 2));
			obj[i].obj_teta = calculate_obj_or_enemy_teta(p_var, &obj[i], NULL);
			obj[i].x_screen = obj[i].obj_teta * (1400 / p_var->fov);
			obj[i].y_screen = (var->window_height / 2)
				+ var->p_infos->up_down_offset;
			i++;
		}
		adjust_rank(obj, nbr_obj);
	}
}

t_health_bar	*init_h_bar(t_player_infos *p_var)
{
	t_health_bar	*res;

	res = (t_health_bar *)malloc(sizeof(*res));
	if (!res)
		panic("malloc failed !\n");
	res->x = 0;
	res->y = 0;
	res->width = 300;
	res->end = (int)floor((double)res->width * ((double)p_var->health
				/ (double)p_var->max_health));
	res->height = 30;
	res->health_str = NULL;
	res->health_img = NULL;
	return (res);
}

t_player_bonus	*init_player_bonus(t_main_s *var, t_player_infos *p_var)
{
	t_player_bonus	*res;

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
	res->h_bar = init_h_bar(p_var);
	return (res);
}
