#include "includes/ps.h"

// void	ff(void)
// {
// 	system("leaks -q cub3D ");
// }

/*  
    START GAME

*/

int main(int ac, char **av)
{
    t_main_s *var;
    t_parse_data *data;

    // atexit(ff);

    data = parse(ac, av);
    var = init_main_var(data);  
    // mlx_set_cursor_mode(var->mlx, MLX_MOUSE_DISABLED);
    work_of_art(var, 1);
    mlx_loops_and_hooks(var);



    (void)data;
    (void)var;
    (void)av;
    (void)ac;
}

/**
 * ONLY PARSING
 * 
*/



// int main(int ac, char **av)
// {
// 	t_parse_data *data;

// 	// atexit(ff);
//     data = parse(ac , av);
//     printf("%d\n", ft_strslen(data->map));
// 	// print_data(data);
// 	free_data(data);
//     // free_split(data->map);
//     // free(data);
//     return 0;
// }
