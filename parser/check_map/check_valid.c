/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 09:25:16 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 19:48:54 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game/ft_game.h"

static int	check_map_wide(char **map, int i, int j)
{
	int t;
	int flag;

	flag = 0;
	t = j - 1;
	while (flag == 0 && map[i][++t] != '\0')
		if (map[i][t] == '1')
			flag = 2;
		else if (map[i][t] == ' ')
			err("Space in map");
	t = j + 1;
	while (--t >= 0 && flag == 2 && map[i][t])
		if (map[i][t] == '1')
			flag = 1;
		else if (map[i][t] == ' ')
			err("Space in map");
	return (flag == 1 ? 1 : 0);
}

static int	check_map_height(char **map, int i, int j)
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
			len = ((int)ft_strlen(map[t - 1]) >= j ? 1 : 0);
		else if (t == 0)
			len = ((int)ft_strlen(map[t]) >= j ? 1 : 0);
		else if (map[t][j] == ' ')
			err("Space in map");
	len = 1;
	i -= 1;
	while (flag == 2 && map[++i] && len)
		if (map[i][j] == '1')
			flag = 1;
		else if (map[i + 1])
			len = ((int)ft_strlen(map[i + 1]) >= j ? 1 : 0);
		else if (!(map[i + 1]))
			len = ((int)ft_strlen(map[i]) >= j ? 1 : 0);
		else if (map[t][j] == ' ')
			err("Space in map");
	return (flag == 1 ? 1 : 0);
}

int			check_valid(t_tx tx)
{
	int		i;
	int		j;
	int		flag;

	flag = 1;
	i = -1;
	if (tx.map == NULL)
		err("Empty map");
	while (flag == 1 && tx.map[++i])
	{
		j = -1;
		if (tx.map[i][0] == '\0')
			err("Invalid map");
		while (flag == 1 && tx.map[i][++j])
			if (tx.map[i][j] == '0' || tx.map[i][j] == '2'
			|| tx.map[i][j] == 'N' || tx.map[i][j] == 'S' || tx.map[i][j] == 'E'
			|| tx.map[i][j] == 'W')
			{
				flag = check_map_wide(tx.map, i, j);
				if (flag)
					flag = check_map_height(tx.map, i, j);
			}
	}
	return (flag);
}
