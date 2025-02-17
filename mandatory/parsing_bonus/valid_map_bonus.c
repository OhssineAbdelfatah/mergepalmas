/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:16:34 by aohssine          #+#    #+#             */
/*   Updated: 2025/02/17 00:02:50 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_pos	first_corner(char **map)
{
	t_pos	indx;

	indx.y_ver = 0;
	while (map[indx.y_ver])
	{
		indx.x_hor = 0;
		while (map[indx.y_ver][indx.x_hor])
		{
			if (map[indx.y_ver][indx.x_hor] == '0' || __direction(map[indx.y_ver][indx.x_hor]) || bonus_obj(map[indx.y_ver][indx.x_hor]))
			{
				return (indx);
			}
			indx.x_hor++;
		}
		indx.y_ver++;
	}
	return (indx);
}

int	check_directions_ver(char **map, t_pos pos)
{
	if (pos.y_ver - 1 >= 0 && pos.x_hor >= (int)ft_strlen(map[pos.y_ver - 1]))
		return (1);
	else if (pos.y_ver - 1 >= 0
		&& pos.x_hor < (int)ft_strlen(map[pos.y_ver - 1])
		&& map[pos.y_ver - 1][pos.x_hor] != '0'
		&& map[pos.y_ver - 1][pos.x_hor] != '1'
		&& !__direction(map[pos.y_ver - 1][pos.x_hor])
		&& !bonus_obj(map[pos.y_ver - 1][pos.x_hor]))
		return (1);
	else if (pos.y_ver + 1 < (int)ft_strslen(map)
		&& pos.x_hor < (int)ft_strlen(map[pos.y_ver + 1])
		&& map[pos.y_ver + 1][pos.x_hor] != '0'
		&& map[pos.y_ver + 1][pos.x_hor] != '1'
		&& !__direction(map[pos.y_ver + 1][pos.x_hor])
		&& !bonus_obj(map[pos.y_ver + 1][pos.x_hor]))
		return (1);
	else if (pos.y_ver + 1 == (int)ft_strslen(map) || pos.y_ver - 1 < 0 )
		return (1);
	return (0);
}

int	check_directions_hor(char **map, t_pos pos)
{
	if (pos.x_hor - 1 >= 0 && map[pos.y_ver][pos.x_hor - 1] != '0'
		&& map[pos.y_ver][pos.x_hor - 1] != '1'
		&& !__direction(map[pos.y_ver][pos.x_hor - 1])
		&& !bonus_obj(map[pos.y_ver][pos.x_hor - 1]))
		return (1);
	else if (pos.x_hor + 1 < (int)ft_strlen(map[pos.y_ver])
		&& map[pos.y_ver][pos.x_hor + 1] != '0'
		&& map[pos.y_ver][pos.x_hor + 1] != '1'
		&& !__direction(map[pos.y_ver][pos.x_hor + 1])
		&& !bonus_obj(map[pos.y_ver][pos.x_hor + 1]))
		return (1);
	else if (pos.x_hor + 1 == (int)ft_strlen(map[pos.y_ver]))
		return (1);
	return (0);
}

int valid_door(char **map, t_pos p)
{
	if(p.x_hor + 1 > (int)ft_strlen(map[p.y_ver]) || p.x_hor - 1 < 0 
		|| p.y_ver + 1 > ft_strslen(map) || p.y_ver - 1 < 0)
		return ((puts("buffer overflow")),1);
	if(map[p.y_ver][p.x_hor - 1] != map[p.y_ver][p.x_hor + 1] && (	
		map[p.y_ver][p.x_hor + 1] != '0' 
		|| map[p.y_ver][p.x_hor + 1] != '1' ))
		return (1);
	if(map[p.y_ver+1][p.x_hor] != map[p.y_ver-1][p.x_hor] && (
		map[p.y_ver-1][p.x_hor] != '0' 
		|| map[p.y_ver-1][p.x_hor ] != '1')) 
		return (1);
	return 0;
}
int	check_line(char **map, t_pos first)
{
	while (map[first.y_ver][first.x_hor])
	{
		if(map[first.y_ver][first.x_hor] =='D' && valid_door(map, first))
			return ((puts("bad door")),1);
		if ((first.y_ver == 0 || first.x_hor == 0)
			&& (map[first.y_ver][first.x_hor] == '0'
			|| __direction(map[first.y_ver][first.x_hor])
			|| bonus_obj(map[first.y_ver][first.x_hor])))
			return (1);
		if (map[first.y_ver][first.x_hor] == '1'
			|| map[first.y_ver][first.x_hor] == ' '
			|| bonus_obj(map[first.y_ver][first.x_hor]))
			first.x_hor++;
		else
		{
			if (check_directions_hor(map, first))
				return (1);
			else if (check_directions_ver(map, first))
				return (1);
			else
				first.x_hor++;
		}
	}
	return (0);
}

int	valid_map(char **map)
{
	t_pos	first;
	int		one_time;

	one_time = 1;
	first.x_hor = 0;
	first.y_ver = 0;
	first = first_corner(map);
	while (map[first.y_ver])
	{
		if (one_time)
			one_time = !one_time;
		else
			first.x_hor = 0;
		if (check_line(map, first))
			return (1);
		first.y_ver++;
	}
	return (0);
}
