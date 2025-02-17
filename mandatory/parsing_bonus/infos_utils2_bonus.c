/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aohssine <aohssine@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:02:28 by aohssine          #+#    #+#             */
/*   Updated: 2025/02/17 17:56:38 by aohssine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	return_type(char *tokens)
{
	int	type;

	type = NO_TYPE;
	if (!ft_strncmp(tokens, "F", 1) && ft_strlen(tokens) == 1)
		type = FLOOR;
	else if (!ft_strncmp(tokens, "C", 1) && ft_strlen(tokens) == 1)
		type = CEILEING;
	else if (!ft_strncmp(tokens, "SO", 2) && ft_strlen(tokens) == 2)
		type = IMG_SO;
	else if (!ft_strncmp(tokens, "NO", 2) && ft_strlen(tokens) == 2)
		type = IMG_NO;
	else if (!ft_strncmp(tokens, "EA", 2) && ft_strlen(tokens) == 2)
		type = IMG_EA;
	else if (!ft_strncmp(tokens, "WE", 2) && ft_strlen(tokens) == 2)
		type = IMG_WE;
	else
		type = NO_TYPE;
	return (type);
}

int	count_occ(char *set, char c)
{
	int	i;

	i = 0;
	while (set && *set)
	{
		if (*set == c)
			i++;
		set++;
	}
	return (i);
}

int	chcek_set_len(char **sets)
{
	int	i;
	int	j;

	i = 0;
	while (sets[i])
	{
		j = 0;
		while (sets[i][j])
		{
			if (sets[i][j] && sets[i][j] != '0')
			{
				if (ft_strlen(&sets[i][j]) > 3)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}
