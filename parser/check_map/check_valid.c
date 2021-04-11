/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 09:25:16 by desausag          #+#    #+#             */
/*   Updated: 2021/04/11 15:12:05 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game/ft_game.h"

static int check_map_wide(char **map, int i, int j)
{
    int t;
    int flag;

    flag = 0;
    t = j - 1;
    while (flag == 0 && map[i][++t] != '\0')
        if (map[i][t] == '1')
            flag = 2;
    t = j + 1;
    while (--t >= 0 && flag == 2 && map[i][t])
        if (map[i][t] == '1')
            flag = 1;
    return (flag == 1 ? 1 : 0);
}
static int check_map_height(char **map, int i, int j)
{
    int t;
    int flag;
    int len;

    flag = 0;
    t = i + 1;
    len = 1;
    while (--t >= 0 && flag == 0 && len)
        if (map[t][j] == '1')
            flag = 2;
        else if (t > 0)
            len = (ft_strlen(map[t - 1]) >= j ? 1 : 0);
        else if (t == 0)
            len = (ft_strlen(map[t]) >= j ? 1 : 0);
    len = 1;
    i -= 1;
    while (flag == 2 && map[++i] && len)
        if (map[i][j] == '1')
            flag = 1;
        else if (map[i + 1])
            len = (ft_strlen(map[i + 1]) >= j ? 1 : 0);
        else if (!(map[i + 1]))
            len = (ft_strlen(map[i]) >= j ? 1 : 0);
    return (flag == 1 ? 1 : 0);
}
int	check_valid(t_tx tx)
{
    char **m;
    int i;
    int j;
    int flag;

    flag = 1;
    i = -1;
    m = tx.map;
    while (flag == 1 && m[++i])
    {
        j = -1;
        while (flag == 1 && m[i][++j])
            if (m[i][j] == '0' || m[i][j] == '2' || m[i][j] == 'N'
            		|| m[i][j] == 'S' || m[i][j] == 'E' || m[i][j] == 'W')
            {
                flag = check_map_wide(m, i, j);//Если на какой-то строке флаг = 0, то выходим из цикла
                if (flag)
                    flag = check_map_height(m, i, j);
            }
    }
    return (flag);
}