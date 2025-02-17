/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:58:39 by aohssine          #+#    #+#             */
/*   Updated: 2025/02/17 16:58:40 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
