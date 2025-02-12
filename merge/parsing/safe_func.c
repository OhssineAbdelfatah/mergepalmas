/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:02:39 by aohssine          #+#    #+#             */
/*   Updated: 2025/02/12 18:07:01 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	**safe__malloc(void)
{
	void	**dt;

	dt = malloc(sizeof(void *));
	if (!dt)
		exit(1);
	return (dt);
}

void	*safe_malloc(void)
{
	void	**dt;

	dt = malloc(sizeof(void));
	if (!dt)
		exit(1);
	return (dt);
}

int	safe_open(char *file, t_pre_data *dt)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(dt);
		ft_putstr_fd("Error open map\n", 2);
		exit(1);
	}
	return (fd);
}
