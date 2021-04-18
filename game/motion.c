/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 09:12:43 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 09:12:43 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

void			go_f(t_all *all, int keycode)
{
	t_cord	tmp;

	if (keycode == W)
	{
		tmp.x = all->plr.pos.x + all->plr.dir.x * SPD;
		tmp.y = all->plr.pos.y + all->plr.dir.y * SPD;
	}
	else
	{
		tmp.x = all->plr.pos.x - all->plr.dir.x * SPD;
		tmp.y = all->plr.pos.y - all->plr.dir.y * SPD;
	}
	if (!(is_wall_cord(all->map, tmp, all->plr.dir)))
		all->plr.pos = tmp;
}

void			go_dir(t_all *all, int keycode)
{
	t_cord	ndir;
	t_cord	tmp;

	if (keycode == A)
		ndir = rttz(all->plr.dir, 0, v_set(0, -1));
	else
		ndir = rttz(all->plr.dir, 0, v_set(0, 1));
	tmp.x = all->plr.pos.x + ndir.x * SPD;
	tmp.y = all->plr.pos.y + ndir.y * SPD;
	if (!(is_wall_cord(all->map, tmp, ndir)))
		all->plr.pos = tmp;
}

int				key_hook(int keycode, t_all *all)
{
	if (keycode == W || keycode == S)
		go_f(all, keycode);
	if (keycode == A || keycode == D)
		go_dir(all, keycode);
	if (keycode == LEFT)
		all->plr.dir = rttz(all->plr.dir, -7, v_set(0.99, 0.12));
	if (keycode == RIGHT)
		all->plr.dir = rttz(all->plr.dir, 7, v_set(0.99, -0.12));
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

double			angle(t_cord begin, t_cord end)
{
	double	q;
	double	a;
	double	b;

	q = begin.x * end.x + begin.y * end.y;
	a = sqrt(pow(begin.x, 2) + pow(begin.y, 2));
	b = sqrt(pow(end.x, 2) + pow(end.y, 2));
	q = q / (a * b);
	return (q);
}

t_cord			rttz(t_cord vector, double angle, t_cord si_co)
{
	t_cord tmp;

	angle = angle * (M_PI / 180);
	if (angle != 0)
		si_co = v_set(cos(angle), sin(angle));
	tmp.x = (vector.x * si_co.x - vector.y * si_co.y);
	tmp.y = (vector.x * si_co.y + vector.y * si_co.x);
	return (tmp);
}
