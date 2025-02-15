#include "../includes/ps.h"

int	gettt_rgba(uint8_t *color)
{
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

t_walls *init_walls(t_main_s *ptr)
{
    t_walls *var;

    var = malloc(sizeof(*var));
    if (!var)
        panic("malloc failed !\n");
    var->distance_prj_plane = (ptr->window_width / 2) / tan(((M_PI / 180) * 60 )/ 2);
    var->wall_hight = 0;
    var->prj_plane_height = square_len / 2;
    return var;
}

t_ray_hit_obj *init_obj()
{
    t_ray_hit_obj *ret;

    ret  = (t_ray_hit_obj *)malloc(sizeof(t_ray_hit_obj));
    if (!ret)
        panic("malloc failed !\n");
    ret->distance = 0;
    ret->from = 0;
    ret->x_intersection = 0;
    ret->y_intersection = 0;
    return ret;
}

t_ray_hit_door *init_door()
{
    t_ray_hit_door *ret;

    ret  = (t_ray_hit_door *)malloc(sizeof(t_ray_hit_door));
    if (!ret)
        panic("malloc failed !\n");
    ret->distance = 0;
    ret->from = 0;
    ret->x_intersection = 0;
    ret->y_intersection = 0;
    return ret;
}

t_rays_bonus *init_bonus_rays()
{
    t_rays_bonus *ret;

    ret = (t_rays_bonus *)malloc(sizeof(t_rays_bonus));
    if (!ret)
        panic("malloc failed !\n");
    ret->hit_a_door = false;
    ret->hit_an_obj = false;
    ret->hit_an_enemy = false;
    ret->door = init_door();
    ret->enemy = NULL;
    // ret->obj = init_obj();
    ret->obj = NULL;
    return ret;
}

t_player_infos *init_player_struct(t_main_s *ptr,char c, int x, int y)
{
    t_player_infos *var;
    var = malloc(sizeof(*var));
    if (!var)
        panic("malloc failed !\n");
    var->y =   y;
    var->x =   x;
    var->move_up_down = 0;
    var->move_left_right = 0;
    var->turn_arround = 0; 
    var->speed = 10;
    var->rotation_speed = (M_PI / 180) * 4;
    var->rays = NULL;
    var->nbr_rays = 0;
    var->fov = (M_PI / 180) * 60;
    if (c == 'E')
        var->rotation_angle = M_PI / 2; 
    if (c == 'W')
        var->rotation_angle = M_PI + (M_PI / 2);
    if (c == 'N')
        var->rotation_angle = M_PI ;
    if (c == 'S')
        var->rotation_angle = 0;
    var->walls = init_walls(ptr);
    // var->walls = NULL;


    /******BONUS*****/
    var->jump_kneel = 0;
    var->look_up_down = 0;
    var->up_down_offset = 0;
    var->alive = true;
    var->health = 100;
    var->max_health = var->health;
    // printf("x >>> %f\n", var->p_infos->x);

    var->p_bonus = init_player_bonus(ptr, var);
    (void)ptr;
    return (var);
}



t_bonus *init_bonus(t_main_s *main)
{
    t_bonus *var;

    var = (t_bonus *)malloc(sizeof(t_bonus));
    if (!var)
        panic("malloc faild! \n");


    var->enemy_text = get_image("../assets/textures/AGAHA1.png");
    var->dead_enemy_text = get_image("../assets/textures/AGAHL0.png");
    var->sky_text = get_image("../assets/sky/Fuzzy Sky/Fuzzy_Sky-Sunset_04-1024x512.png");  
    var->door = get_image("../assets/textures/doortile.png");

    var->mouse_x = (main->window_width) / 2;
    var->mouse_y = (main->window_height) / 2;
    var->gun_in_hand_text0 = NULL;
    var->floor_text = get_image("../assets/floor/Brick/Brick_18-128x128.png");
    var->pillar_img = get_image("../assets/textures/EHEDC0.png");

    var->crosshair =  safe_load("../assets/textures/techno1.png");
    var->crosshair_img = mlx_texture_to_image(main->mlx, var->crosshair);
    mlx_resize_image(var->crosshair_img, main->window_width / 14, main->window_height / 8);

    var->gun_in_hand[0] =  safe_load("../assets/textures/RGLGD0.png");
    var->gun_in_hand[1] =  safe_load("../assets/textures/RGLFA0.png");
    var->gun_in_hand[2] =  safe_load("../assets/textures/RGLFB0.png");
    var->gun_in_hand[3] =  safe_load("../assets/textures/RGLFC0.png");
    var->gun_in_hands_img[0] = mlx_texture_to_image(main->mlx, var->gun_in_hand[0]);
    var->gun_in_hands_img[1] = mlx_texture_to_image(main->mlx, var->gun_in_hand[1]);
    var->gun_in_hands_img[2] = mlx_texture_to_image(main->mlx, var->gun_in_hand[2]);
    var->gun_in_hands_img[3] = mlx_texture_to_image(main->mlx, var->gun_in_hand[3]);
    mlx_resize_image(var->gun_in_hands_img[0], main->window_width - ( main->window_width / 3), main->window_height - ( main->window_height / 3));
    mlx_resize_image(var->gun_in_hands_img[1], main->window_width - ( main->window_width / 3), main->window_height - ( main->window_height / 3));
    mlx_resize_image(var->gun_in_hands_img[2], main->window_width - ( main->window_width / 3), main->window_height - ( main->window_height / 3));
    mlx_resize_image(var->gun_in_hands_img[3], main->window_width - ( main->window_width / 3), main->window_height - ( main->window_height / 3));
    var->gun_in_hands_img[1]->enabled =false;
    var->gun_in_hands_img[2]->enabled =false;
    var->gun_in_hands_img[3]->enabled =false;
    var->nbr_enemies = 0;
    var->nbr_obj = 0;
    return (var);
}

t_mini_map *init_mini_map(void *mlx, int width, int height)
{
    t_mini_map *var;

    var = malloc(sizeof(t_mini_map));
    if (!var)
        panic("malloc faild !\n");
    var->mini_square_len = 32;
    var->minimap_height = 32 * 5;
    var->minimap_width = 32 * 7;
    var->p_y = var->minimap_height / 2;
    var->p_x = var->minimap_width / 2;
    var->img3 = mlx_new_image(mlx, var->minimap_width, var->minimap_height);
    (void)height;
    (void)width;
    return var;
}



void print_pixesl(t_text *img)
{
    int i ,j ;

    i = 0;
    while(i < img->hieght)
    {
        j= 0;
        while(j < img->width)
        {
            printf("pix[%d][%d] |%d|\n",i , j , img->pixels[i][j]);
            j++;
        }
        i++;
    }
}

/***
 * images stored in array in a strict order 
 * following real direction N -> E -> S -> W 
*/
t_text **init_textures(t_main_s *var)
{
    t_text **text;

    text = malloc(sizeof(t_text*) * 4);
    if(!text)
        panic("malloc failed !\n");
    text[0] = get_image(var->parse->tex_no);
    text[1] = get_image(var->parse->tex_ea);
    text[2] = get_image(var->parse->tex_so);
    text[3] = get_image(var->parse->tex_we);
    return text;
}

t_main_s *init_main_var(t_parse_data *parse)
{
    t_main_s *var;
    var = malloc(sizeof(*var));
    if (!var)
        panic("malloc failed !\n");
    var->window_height = 800;
    var->window_width = 1400;
    var->p_infos = NULL;
    var->parse = parse;
    var->map = parse->map;

    var->map_hight = ft_dstr_len(var->map);
    var->map_width = ft_strlen(var->map[0]);

    var->mlx = mlx_init(var->window_width,  var->window_height, "cub3D", false);
    // var->img = mlx_new_image(var->mlx, (10  * square_len * scale_of_minimap), (var->map_hight * scale_of_minimap * square_len));
   
    var->img2 = mlx_new_image(var->mlx, var->window_width, var->window_height);
    var->img3 = mlx_new_image(var->mlx, var->window_width, var->window_height);

    var->mini_map = init_mini_map(var->mlx, var->window_width, var->window_height);
    var->text = init_textures(var);

    var->bonus = init_bonus(var);
    var->start_frame = get_time_mil();
    // gettimeofday(&var->tv, NULL);
    //  BONUS PART :: 
    // var->mouse_x = (var->window_width * square_len) / 2;
    // init_textures(var);
    return var;
}

t_ray_info *init_rays(t_main_s *ptr, double ray_angle, double angle_incremet)
{
    int i = 0;
    t_ray_info *var;
    var = malloc(sizeof(*var) * ptr->p_infos->nbr_rays);
    if (!var)
        panic("malloc failed !\n");
    while (i <  ptr->p_infos->nbr_rays)
    {
        var[i].angle = 0;
        var[i].distance = 0;
        var[i].horzt_or_vert = 0;
        var[i].facing_left = false;
        var[i].facing_right = false;
        var[i].x_last_intersection = 0;
        var[i].y_last_intersection = 0;
        var[i].wall_dir = 0;
        var[i].bonus_rays = init_bonus_rays();
        // var[i].bonus_rays = NULL;
        i++;
        ray_angle += angle_incremet; 
    }
    return var;
}
