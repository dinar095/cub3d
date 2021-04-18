/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:58:36 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 09:00:49 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

t_cord			is_sprite(char **map, t_cord dot, t_cord ray)
{
	int	x;
	int	y;

	if (ray.x < 0)
		x = (int)ceil(dot.x) - 1;
	else
		x = (int)dot.x;
	if (ray.y <= 0)
		y = (int)ceil(dot.y) - 1;
	else
		y = (int)dot.y;
	if (map[y][x] == '2')
		return (v_set(x, y));
	else
		return (v_set(-1, -1));
}

void			init_sprite(t_all *all, t_cord cross)
{
	int		i;
	t_cord	vec;
	double	ugol;
	int		znak;

	i = -1;
	while (++i < all->spr_co)
	{
		if ((int)all->sp[i].pos.x == (int)cross.x
			&& (int)all->sp[i].pos.y == (int)cross.y && all->sp[i].vis == 0)
		{
			all->sp[i].vis = 1;
			vec = v_set(all->sp[i].pos.x - all->plr.pos.x,
						all->sp[i].pos.y - all->plr.pos.y);
			znak = all->ray0.x * vec.y - all->ray0.y * vec.x < 0 ? -1 : 1;
			ugol = acos(angle(all->ray0, vec)) * znak * 180 / M_PI;
			all->sp[i].cent = ugol / 46 * all->tx.width;
		}
	}
}

void			draw_sprite(t_all *all, t_sprite spr, double *zbuf)
{
	t_int	i;
	t_cord	h;
	t_cord	y;
	t_int	tmp;
	int		color;

	h.x = all->tx.height / len_ray(all->plr.pos, spr.pos);
	y.x = all->tx.height / 2 - h.x / 2;
	y.y = all->tx.height / 2 + h.x / 2;
	h.y = all->txre_img[4].w / h.x;
	i.i = spr.cent - h.x / 2;
	while (++i.i < (spr.cent + h.x / 2))
		if (i.i > 0 && i.i < all->tx.width)
		{
			tmp.i = (i.i - spr.cent + h.x / 2) * h.y;
			i.j = -1;
			while (++i.j < y.y)
				if (i.j > y.x && i.j < y.y && y.x <= zbuf[i.i])
				{
					tmp.j = (int)(h.y * (i.j - y.x));
					if ((color = get_color(all->txre_img[4], tmp.i, tmp.j)))
						my_mlx_pixel_put(all, i.i, i.j, color);
				}
		}
}

void			print_sprite(t_all *all, double *zbuf)
{
	int	i;

	i = -1;
	while (++i < all->spr_co)
		all->sp[i].dist = len_ray(all->sp[i].pos, all->plr.pos);
	sort_sprite(all);
	i = -1;
	while (++i < all->spr_co)
	{
		if (all->sp[i].vis)
			draw_sprite(all, all->sp[i], zbuf);
	}
}

void			sort_sprite(t_all *all)
{
	t_sprite	nwsprt;
	int			location;
	int			i;

	i = 1;
	while (i < all->spr_co)
	{
		nwsprt = all->sp[i];
		location = i - 1;
		while (location >= 0 && all->sp[location].dist < nwsprt.dist)
		{
			all->sp[location + 1] = all->sp[location];
			location = location - 1;
		}
		all->sp[location + 1] = nwsprt;
		i++;
	}
}
