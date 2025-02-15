#include "../includes/ps.h"


mlx_texture_t *safe_load(char *path)
{
    mlx_texture_t *img;

    img = mlx_load_png(path);
    if(!img)
    {
        ft_putstr_fd(path, 2);
        panic (" ,load png failed !\n");
    }
    return img ;
}

t_text *safe_img_cnv(char *path_to_img)
{
    mlx_texture_t *img;
    img = safe_load(path_to_img);
    return get_image(img);
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