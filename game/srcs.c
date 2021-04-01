/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:02:36 by desausag          #+#    #+#             */
/*   Updated: 2021/04/01 20:51:11 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"
void            my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char    *dst;

	if (x > 0 && y > 0 && x < all->textures.width && y < all->textures.height)//допилить
	{
        dst = all->win.addr + (y * all->win.line_l + x * (all->win.bpp / 8));//
        *(unsigned int *) dst = color;
    }
}

void init_texture(t_all *all)
{
	all->txre_img[0].img = mlx_xpm_file_to_image(all->win.mlx, all->textures.no, &all->txre_img[0].w, &all->txre_img[0].h);
	all->txre_img[1].img = mlx_xpm_file_to_image(all->win.mlx, all->textures.so, &all->txre_img[1].w, &all->txre_img[1].h);
	all->txre_img[2].img = mlx_xpm_file_to_image(all->win.mlx, all->textures.we, &all->txre_img[2].w, &all->txre_img[2].h);
	all->txre_img[3].img = mlx_xpm_file_to_image(all->win.mlx, all->textures.ea, &all->txre_img[3].w, &all->txre_img[3].h);
	all->txre_img[4].img = mlx_xpm_file_to_image(all->win.mlx, all->textures.s, &all->txre_img[4].w, &all->txre_img[4].h);
}//need free pa

t_cord net_point(t_cord ray, t_cord pos)
{
	t_cord tmp;
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

unsigned int get_color(t_data txre_img, int x, int y)
{
	char *dst;
	txre_img.addr = mlx_get_data_addr(txre_img.img, &txre_img.bpp, &txre_img.line_l, &txre_img.endian);
	if (x >= 0 && y >= 0 && x <= txre_img.w && y <= txre_img.h)
	{
		dst = txre_img.addr + (y * txre_img.line_l + x * (txre_img.bpp / 8));
		return (*(unsigned int *) dst);
	}
}

t_cord fwd_pnt(t_cord ray, t_cord pnt, int flag)
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

double len_ray(t_cord ray1, t_cord ray2)
{
	return (sqrt(pow(ray1.y - ray2.y, 2) + pow(ray1.x - ray2.x, 2)));
}


int is_wall_cord(char **map,t_cord dot, t_cord ray)
{
    int x;
    int y;
    if (ray.x < 0)
        x = (int)ceil(dot.x) - 1;
    else
        x =(int)dot.x;
    if (ray.y <= 0)
        y = (int)ceil(dot.y) - 1;
    else
        y = (int)dot.y;
    if (map[y][x] != '1')
        return 0;
    else
        return 1;
}

t_cord 			v_set(double val_x, double val_y)
{
	t_cord		res;
	res.x = val_x;
	res.y = val_y;
	return (res);
}

t_cord is_sprite(char **map,t_cord dot, t_cord ray)
{
	int x;
	int y;
	if (ray.x < 0)
		x = (int)ceil(dot.x) - 1;
	else
		x =(int)dot.x;
	if (ray.y <= 0)
		y = (int)ceil(dot.y) - 1;
	else
		y = (int)dot.y;
	if (map[y][x] == '2')
		return v_set(x, y);
	else
		return (v_set(-1,-1));
}
int             key_hook(int keycode, t_all *all)
{
	t_cord tmp;
	t_cord nDir;
	tmp = v_set(0,0);
	if (keycode == W || keycode == S)
	{
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
	if (keycode == A || keycode == D)
	{
		if (keycode == A)
			nDir = rotateZ(all->plr.dir, -90);
		else
			nDir = rotateZ(all->plr.dir, 90);
		tmp.x = all->plr.pos.x + nDir.x * SPD;
		tmp.y = all->plr.pos.y + nDir.y * SPD;
		if (!(is_wall_cord(all->map, tmp, nDir)))
			all->plr.pos = tmp;
	}
	if (keycode == LEFT)
		all->plr.dir = rotateZ(all->plr.dir, -7);
	if (keycode == RIGHT)
		all->plr.dir = rotateZ(all->plr.dir, 7);
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
}

void    init_img(t_all *all)
{
	all->win.img= mlx_new_image(all->win.mlx, all->textures.width, all->textures.height);
	all->win.addr = mlx_get_data_addr(all->win.img, &(all->win.bpp),&(all->win.line_l),
								  &(all->win.endian));
}

t_cord   crc(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b)//точка пересечения по точке и вектору
{
	t_cord dot_c;
	double  q;
	double  n;

	if (dot_b.x == dot_a.x && dot_b.y == dot_a.y)
		return (dot_b);
	ft_bzero(&dot_c, sizeof(t_cord));
	if (a.y != 0)
	{
		if (a.y == 0)
		{
			write(0, "1", 1);
		}
		q = - a.x / a.y;
		n = ((dot_b.x - dot_a.x) + q * (dot_b.y - dot_a.y)) /
			(b.x + b.y * q);
	}
	else if (b.y != 0)
		n = (dot_b.y - dot_a.y) / b.y;
	else
	{
		ft_putstr_fd("Not cross", 1);
		return (dot_a); // Затычка!!!!!!!!!!!!!!
	}
	dot_c.x = dot_b.x - n * b.x;
	dot_c.y = dot_b.y - n * b.y;
	return (dot_c);
}
void	null_sprites(t_all *all)
{
	int i;


	i = -1;
	while (++i < all->sprite->co)
		all->sprite[i].vis = 0;
}
double angle(t_cord begin, t_cord end)
{
	double q;
	double a;
	double b;
	q = begin.x * end.x + begin.y*end.y;//скалярное произведение векторов
	a = sqrt(pow(begin.x, 2) + pow(begin.y,2));
	b = sqrt(pow(end.x, 2) + pow(end.y,2));
	q = q / (a * b);
	return (q);
}
t_cord rotateZ(t_cord vector,double angle)
{ // angle in radians

//normalize(vector); // No  need to normalize, vector is already ok...
	angle = angle * (M_PI/180);
	t_cord tmp;
	tmp.x = (vector.x * cos(angle) - vector.y * sin(angle));

	tmp.y = (vector.x * sin(angle) + vector.y * cos(angle));

	return (tmp);
}