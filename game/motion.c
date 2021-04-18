/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 09:12:43 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 13:33:49 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

void			go_f(t_all *all)
{
	t_cord	tmp;

	if (all->w == 1)
	{
		tmp.x = all->plr.pos.x + all->plr.dir.x * SPD;
		tmp.y = all->plr.pos.y + all->plr.dir.y * SPD;
	}
	if (all->s == 1)
	{
		tmp.x = all->plr.pos.x - all->plr.dir.x * SPD;
		tmp.y = all->plr.pos.y - all->plr.dir.y * SPD;
	}
	if (!(is_wall_cord(all->map, tmp, all->plr.dir)))
		all->plr.pos = tmp;
}

void			go_dir(t_all *all)
{
	t_cord	ndir;
	t_cord	tmp;

	if (all->a == 1)
		ndir = rttz(all->plr.dir, 0, v_set(0, -1));
	else if (all->d == 1)
		ndir = rttz(all->plr.dir, 0, v_set(0, 1));
	tmp.x = all->plr.pos.x + ndir.x * SPD;
	tmp.y = all->plr.pos.y + ndir.y * SPD;
	if (!(is_wall_cord(all->map, tmp, ndir)))
		all->plr.pos = tmp;
}
int				k_prs(int keycode, t_all *all)
{
	if (keycode == W)
		all->w = 1;
	if (keycode == S)
		all->s = 1;
	if (keycode == A)
		all->a = 1;
	if (keycode == D)
		all->d = 1;
	if (keycode == LEFT)
		all->lf = 1;
	if (keycode == RIGHT)
		all->lr = 1;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int				k_rel(int keycode, t_all *all)
{
	if (keycode == W)
		all->w = 0;
	if (keycode == S)
		all->s = 0;
	if (keycode == A)
		all->a = 0;
	if (keycode == D)
		all->d = 0;
	if (keycode == LEFT)
		all->lf = 0;
	if (keycode == RIGHT)
		all->lr = 0;
	return (0);
}

int				key_hook(t_all *all)
{
	if (all->w == 1 || all->s == 1)
		go_f(all);
	if (all->a == 1 || all->d == 1)
		go_dir(all);
	if (all->lf)
		all->plr.dir = rttz(all->plr.dir, -2, v_set(0.99, 0.12));
	if (all->lr)
		all->plr.dir = rttz(all->plr.dir, 2, v_set(0.99, -0.12));
	draw_screen(all);
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
