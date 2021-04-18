/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:39:04 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 08:42:43 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game/ft_game.h"

void			cr_pos(t_tx *tx, t_int dir, t_int pos)
{
	tx->plr.dir.x = dir.i;
	tx->plr.dir.y = dir.j;
	tx->plr.pos.y = pos.i + 0.5;
	tx->plr.pos.x = pos.j + 0.5;
	tx->map[pos.i][pos.j] = '0';
}

void			cr_plr(t_tx *tx, t_int i_j)
{
	if (ft_strchr("NSWE", tx->map[i_j.i][i_j.j]) && tx->plr.dir.y != -2)
		err("Invalid player");
	else if (tx->map[i_j.i][i_j.j] == 'N')
		cr_pos(tx, v_int(0, -1), v_int(i_j.i, i_j.j));
	else if (tx->map[i_j.i][i_j.j] == 'S')
		cr_pos(tx, v_int(0, 1), v_int(i_j.i, i_j.j));
	else if (tx->map[i_j.i][i_j.j] == 'E')
		cr_pos(tx, v_int(-1, 0), v_int(i_j.i, i_j.j));
	else if (tx->map[i_j.i][i_j.j] == 'W')
		cr_pos(tx, v_int(1, 0), v_int(i_j.i, i_j.j));
}

void			parse_plr(t_tx *tx, t_all *all)
{
	t_int	i_j;
	int		w;
	t_cord	art[10000];

	i_j.i = -1;
	w = 0;
	while (tx->map[++i_j.i])
	{
		i_j.j = -1;
		while (tx->map[i_j.i][++i_j.j])
			if (ft_strchr("NSEW01 ", tx->map[i_j.i][i_j.j]))
				cr_plr(tx, i_j);
			else if (tx->map[i_j.i][i_j.j] == '2')
				art[w++] = v_set(i_j.j + 0.5, i_j.i + 0.5);
			else
				err("Invalid arguments in map");
	}
	if (tx->plr.dir.y == -2)
		err("No player in map");
	all->spr_co = w;
	if (all->spr_co > 0)
		mem_sprt(all, art);
}
