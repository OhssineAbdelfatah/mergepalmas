/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blacksniper <blacksniper@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:22:54 by aohssine          #+#    #+#             */
/*   Updated: 2025/02/17 02:08:20 by blacksniper      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	check_unicty_infos(t_map_lst *list)
{
	t_map_lst	*tmp;

	if (list_size(list) != 6)
		return ((printf("psp\n")), 1);
	while (list)
	{
		tmp = list->next;
		while (tmp)
		{
			if (list->type > 5 || list->type == tmp->type)
				return (1);
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (0);
}

t_map_lst	*get_map_infos(int fd_map)
{
	t_map_info	dt;

	dt.count = 0;
	dt.map_lst = NULL;
	dt.tail = NULL;
	while (dt.count < 6)
	{
		dt.line = get_next_line(fd_map);
		if (dt.line == NULL)
			break ;
		if (dt.line && dt.line[0] == '\n')
		{
			free(dt.line);
			continue ;
		}
		dt.line = delete_nl(dt.line);
		dt.type = get_type(dt.line);
		if (dt.type == NO_TYPE)
			return (free_map(dt.map_lst), free(dt.line), get_next_line(-1),
				NULL);
		dt.count++;
		dt.nd = create_node(dt.line, dt.type);
		add_back(&dt.map_lst, &dt.tail, dt.nd);
	}
	return (dt.map_lst);
}

void	fill_colors(t_pre_data *dt)
{
	char	***sets;
	char	*set1;
	char	*set2;
	int		count;

	count = 0;
	sets = (char ***)malloc(2 * sizeof(char **));
	set1 = fetch_index_splited(find_info_value(FLOOR, dt->info));
	sets[0] = ft_split(set1, ',');
	set2 = fetch_index_splited(find_info_value(CEILEING, dt->info));
	sets[1] = ft_split(set2, ',');
	dt->data->clr_f = malloc(3 * sizeof(int));
	dt->data->clr_c = malloc(3 * sizeof(int));
	while (count < 3)
	{
		dt->data->clr_f[count] = ft_atoi(sets[0][count]);
		dt->data->clr_c[count] = ft_atoi(sets[1][count]);
		count++;
	}
	free(set1);
	free(set2);
	free_split(sets[0]);
	free_split(sets[1]);
	free(sets);
	return ;
}

void	fill_data(t_pre_data *dt)
{
	dt->data->tex_ea = fetch_index_splited(find_info_value(IMG_EA, dt->info));
	dt->data->tex_so = fetch_index_splited(find_info_value(IMG_SO, dt->info));
	dt->data->tex_we = fetch_index_splited(find_info_value(IMG_WE, dt->info));
	dt->data->tex_no = fetch_index_splited(find_info_value(IMG_NO, dt->info));
	dt->data->pos = malloc(sizeof(t_pos));
	find_pos(dt->data->map, dt->data->pos);
	dt->data->dir = dt->data->map[dt->data->pos->y_ver][dt->data->pos->x_hor];
	fill_colors(dt);
	return ;
}

void	*free_error(t_pre_data *dt, int f_dt_map, int f_dt_data_map)
{
	free_map(dt->info);
	if (f_dt_map)
		free_map(dt->map);
	if (f_dt_data_map)
		free_split(dt->data->map);
	free(dt->data);
	free(dt);
	return (NULL);
}

t_pre_data	*read_file(char *file)
{
	t_pre_data	*dt;
	int			fd_map;

	dt = (t_pre_data *)malloc(sizeof(t_pre_data));
	dt->data = (t_parse_data *)malloc(sizeof(t_parse_data));
	if (!dt || !dt->data)
		return (NULL);
	fd_map = safe_open(file, dt);
	dt->info = get_map_infos(fd_map);
	if (check_unicty_infos(dt->info))
		return (printf("unicty err\n"), free_error(dt, 0, 0));
	if (dt->info)
	{
		dt->map = check_map(fd_map);
		if (!dt->map)
			return (close(fd_map), free_error(dt, 1, 0));
		if (parse_map(dt->map))
			return (close(fd_map), free_error(dt, 1, 0));
		dt->data->map = list_to_array(dt->map);
		if (!dt->data->map)
			return (close(fd_map), free_error(dt, 1, 1));
		if (valid_map(dt->data->map))
			return (close(fd_map), free_error(dt, 1, 1));
	}
	return (fill_data(dt), free_map(dt->map), close(fd_map), dt);
}

char	**split2(char *base)
{
	char	**strs;
	char	**new;

	new = NULL;
	strs = ft_split(base, 32);
	if (!strs)
		return (NULL);
	if (ft_strslen(strs) == 1)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(strs[0]);
		new[1] = NULL;
	}
	else if (ft_strslen(strs) > 1)
	{
		new = (char **)malloc(sizeof(char *) * 3);
		if (!new)
			return (NULL);
		new[0] = ft_strdup(strs[0]);
		new[1] = ft_strdup(ft_strchr(base, strs[1][0]));
		new[2] = NULL;
	}
	return (free_split(strs), new);
}
