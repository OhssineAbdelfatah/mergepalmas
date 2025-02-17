#include "../includes/parsing.h"

void	ff(void)
{
	system("leaks -q cub3D ");
}

// int	main(int ac, char **av)
// {
// 	t_parse_data	*data;

// 	// atexit(ff);
// 	data = parse(ac, av);
// 	printf("%d\n", ft_strslen(data->map));
// 	// print_data(data);
// 	free_data(data);
// 	// free_split(data->map);
// 	// free(data);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_parse_data	*data;

	data = parse(ac, av);
	printf("%d\n", ft_strslen(data->map));
	free_data(data);
	return (0);
}
