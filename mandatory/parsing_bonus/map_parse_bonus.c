/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:02:37 by aohssine          #+#    #+#             */
/*   Updated: 2025/02/16 23:28:02 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	__direction(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

int	is_valid_obj(char c)
{
	return (__direction(c) || c == '0' || c == '1' || c == ' ' || c == 'O' || c == 'e' || c == 'D');
}

int	contain_line(char *line)
{
	return (line && (only_spaces(line) || ft_strlen(line) == 0));
}

int	verify_obj(char *arr, int *dir)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!is_valid_obj(arr[i]))
		{
			// printf(">>>%c", arr[i]);
			return (printf("%c invalid obj\n", arr[i]), 1);
		}
		if (__direction(arr[i]))
			(*dir)++;
		i++;
	}
	return (0);
}

int	parse_map(t_map_lst *map_dbl)
{
	int	dir;

	dir = 0;
	while (map_dbl)
	{
		if (verify_obj(map_dbl->value, &dir) )
			return (1);
		else if ( contain_line(map_dbl->value))
			return (printf("map contain a \\ n \n"),1);
		map_dbl = map_dbl->next;
	}
	if (dir != 1)
		return ((puts("hena")),1);
	return (0);
}
