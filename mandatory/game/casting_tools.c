/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilaasri <ilaasri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 23:49:36 by ilaasri           #+#    #+#             */
/*   Updated: 2025/02/14 23:49:37 by ilaasri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ps.h"

int hit_a_door(t_main_s *var, double xintersection, double yintersection, int i)
{
    int x;
    int y;

    x = (int)floor(xintersection / square_len);
    y = (int)floor(yintersection / square_len);
    if (y < 0 || x < 0 || x >= var->map_hight || y > (int)ft_strlen(var->map[x]))
        return 0;
    if (var->map[x][y] == 'D')
        return 1;
    (void)i;
    return 0;
}

int hit_a_wall(t_main_s *var, double xintersection, double yintersection, int i)
{
    int x;
    int y;

    x = (int)floor(xintersection / square_len);
    y = (int)floor(yintersection / square_len);
    if (y < 0 || x < 0 || x >= var->map_hight || y > (int)ft_strlen(var->map[x]))
        return 1;
    if (var->map[x][y] == '1')
        return 1;
    (void)i;
    return 0;
}
