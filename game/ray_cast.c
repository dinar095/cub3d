/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 08:50:22 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 08:57:15 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

t_cord			net_point(t_cord ray, t_cord pos)
{
	t_cord	tmp;

	if (ray.x > 0)
		tmp.x = ceil(pos.x);
	if (ray.x <= 0)
		tmp.x = floor(pos.x);
	if (ray.y > 0)
		tmp.y = ceil(pos.y);
	if (ray.y <= 0)
		tmp.y = floor(pos.y);
	return (tmp);
}

t_cord			fwd_pnt(t_cord ray, t_cord pnt, int flag)
{
	if (flag > 0)
	{
		if (ray.x > 0)
			pnt.x++;
		if (ray.x < 0)
			pnt.x--;
	}
	else
	{
		if (ray.y > 0)
			pnt.y++;
		if (ray.y < 0)
			pnt.y--;
	}
	return (pnt);
}

int				is_wall_cord(char **map, t_cord dot, t_cord ray)
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
	if (map[y][x] != '0' && map[y][x] != '2' && map[y][x] != ' ')
		return (1);
	else
		return (0);
}

t_cord			crc(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b)
{
	t_cord	dot_c;
	t_cord	q_n;

	if (dot_b.x == dot_a.x && dot_b.y == dot_a.y)
		return (dot_b);
	ft_bzero(&dot_c, sizeof(t_cord));
	if (a.y != 0)
	{
		q_n.x = -a.x / a.y;
		q_n.y = ((dot_b.x - dot_a.x) + q_n.x * (dot_b.y - dot_a.y)) /
				(b.x + b.y * q_n.x);
	}
	else if (b.y != 0)
		q_n.y = (dot_b.y - dot_a.y) / b.y;
	else
		q_n.y = (dot_b.y - dot_a.y) / 0.0000001;
	dot_c.x = dot_b.x - q_n.y * b.x;
	dot_c.y = dot_b.y - q_n.y * b.y;
	return (dot_c);
}

double			print_wall(t_cord crs, t_all *all, t_int x_s, t_cord ray)
{
	t_cord	h_dis;
	t_cord	y;
	t_cord	i_k;
	t_int	s_t;

	i_k.x = -1;
	s_t.i = x_s.j;
	h_dis.y = len_ray(all->plr.pos, crs) * angle(all->plr.dir, ray);
	h_dis.x = all->tx.height / (h_dis.y);
	y.x = all->tx.height / 2 - h_dis.x / 2;
	y.y = all->tx.height / 2 + h_dis.x / 2;
	i_k.y = all->txre_img[x_s.j].h / h_dis.x;
	while (++i_k.x <= all->tx.height)
	{
		if (i_k.x > y.x && i_k.x < y.y)
		{
			s_t.j = (int)(i_k.y * (i_k.x - y.x));
			my_mlx_pixel_put(all, x_s.i, i_k.x, vis(all, s_t, crs, ray));
		}
		else if (i_k.x <= y.x)
			my_mlx_pixel_put(all, x_s.i, i_k.x, all->tx.f);
		else if (i_k.x >= y.y)
			my_mlx_pixel_put(all, x_s.i, i_k.x, all->tx.c);
	}
	return (y.x);
}
