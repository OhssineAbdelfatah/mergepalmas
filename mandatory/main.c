#include "includes/ps.h"

int	main(int ac, char **av)
{
	t_main_s		*var;
	t_parse_data	*data;

	data = parse(ac, av);
	var = init_main_var(data);
	work_of_art(var, 1);
	mlx_loops_and_hooks(var);
	(void)ac;
}
