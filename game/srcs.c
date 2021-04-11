/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:02:36 by desausag          #+#    #+#             */
/*   Updated: 2021/04/11 14:53:15 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

void			my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < all->tx.width && y < all->tx.height)
	{
		dst = all->win.addr + (y * all->win.line_l + x * (all->win.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void		init_bmp_header(t_all *all, int fd)
{
	int				v;

	write(fd, "BM", 2);
	v = 14 + 40 + all->tx.width * all->win.bpp / 8 * all->tx.height;
	write(fd, &v, 4);
	write(fd, "\0\0\0\0", 4);
	v = 14 + 40;
	write(fd, &v, 4);
	v = 40;
	write(fd, &v, 4);
	write(fd, &all->tx.width, 4);
	write(fd, &all->tx.height, 4);
	v = 1;
	write(fd, &v, 2);
	write(fd, &all->win.bpp, 2);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 24);
}

void			screen_image(t_all *all)
{
	char			*file_name;
	int				fd;
	int				i;

	file_name = "screen.bmp";
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		err("Can't open file\n");
	init_bmp_header(all, fd);
	i = all->tx.height;
	while (i-- > 0)
	{
		write(fd, (all->win.addr + i * all->win.line_l),
			(all->tx.width * all->win.bpp / 8));
	}
	close(fd);
	exit(0);
}

void			init_texture(t_all *all)
{
	all->txre_img[0].img = mlx_xpm_file_to_image(all->win.mlx,
			all->tx.no, &all->txre_img[0].w, &all->txre_img[0].h);
	all->txre_img[1].img = mlx_xpm_file_to_image(all->win.mlx,
			all->tx.so, &all->txre_img[1].w, &all->txre_img[1].h);
	all->txre_img[2].img = mlx_xpm_file_to_image(all->win.mlx,
			all->tx.we, &all->txre_img[2].w, &all->txre_img[2].h);
	all->txre_img[3].img = mlx_xpm_file_to_image(all->win.mlx,
			all->tx.ea, &all->txre_img[3].w, &all->txre_img[3].h);
	all->txre_img[4].img = mlx_xpm_file_to_image(all->win.mlx,
			all->tx.s, &all->txre_img[4].w, &all->txre_img[4].h);
}

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

unsigned int	vis(t_all *all, t_int s_t, t_cord cross, t_cord ray)
{
	int	tmp1;
	int	wall;

	if (s_t.i == 1)
	{
		if (ray.y > 0)
			wall = 1;
		else
			wall = 0;
		tmp1 = (int)((cross.x - floor(cross.x)) * all->txre_img[wall].w);
	}
	else if (s_t.i == 0)
	{
		if (ray.x > 0)
			wall = 3;
		else
			wall = 2;
		tmp1 = (int)((cross.y - floor(cross.y)) * all->txre_img[wall].w);
	}
	return (get_color(all->txre_img[wall], tmp1, s_t.j));
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

int				check_ext(const char *f_name)
{
	int	c;

	c = ft_strlen(f_name);
	if (c > 6 && !ft_strncmp(f_name + (c - 4), ".cub", 4))
		return (1);
	return (0);
}

unsigned int	get_color(t_data txre_img, int x, int y)
{
	char	*dst;

	txre_img.addr = mlx_get_data_addr(txre_img.img, &txre_img.bpp,
			&txre_img.line_l, &txre_img.endian);
	if (x >= 0 && y >= 0 && x <= txre_img.w && y <= txre_img.h)
	{
		dst = txre_img.addr + (y * txre_img.line_l + x * (txre_img.bpp / 8));
		return (*(unsigned int *)dst);
	}
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

double			len_ray(t_cord ray1, t_cord ray2)
{
	return (sqrt(pow(ray1.y - ray2.y, 2) + pow(ray1.x - ray2.x, 2)));
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
	if (map[y][x] != '0')
		return (1);
	else
		return (0);
}

t_cord			v_set(double val_x, double val_y)
{
	t_cord		res;

	res.x = val_x;
	res.y = val_y;
	return (res);
}

t_int			v_int(int val_x, int val_y)
{
	t_int		res;

	res.i = val_x;
	res.j = val_y;
	return (res);
}

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
}

void			check_display_resolution(t_all *all)
{
	int	wide;
	int	height;

	if (!all->save)
	{
		mlx_get_screen_size(all->win.mlx, &wide, &height);
		if (wide < all->tx.width)
			all->tx.width = wide;
		if (height < all->tx.height)
			all->tx.height = height;
	}
}

void			init_sprite(t_all *all, t_cord cross)
{
	int		i;
	t_cord	vec;
	double	ugol;
	int		znak;

	i = -1;
	while (++i < all->sp->co)
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

double			print_sprite(t_all *all, double *zbuf)
{
	int	i;

	i = -1;
	while (++i < all->sp->co)
		all->sp[i].dist = len_ray(all->sp[i].pos, all->plr.pos);
	sort_sprite(all);
	i = -1;
	while (++i < all->sp->co)
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
	while (i < all->sp[0].co)
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

void			init_img(t_all *all)
{
	all->win.img = mlx_new_image(all->win.mlx, all->tx.width,
			all->tx.height);
	all->win.addr = mlx_get_data_addr(all->win.img, &(all->win.bpp),
			&(all->win.line_l), &(all->win.endian));
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

void			null_sprites(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->sp->co)
		all->sp[i].vis = 0;
}

void			err(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	exit(1);
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
