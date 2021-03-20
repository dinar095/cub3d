/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:02:36 by desausag          #+#    #+#             */
/*   Updated: 2021/03/20 18:02:36 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"
void            my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char    *dst;

	if (x > 0 && y > 0 && x < 1600 && y < 900)//допилить
	{
        dst = all->win->addr + (y * all->win->line_l + x * (all->win->bpp / 8));//
        *(unsigned int *) dst = color;
    }
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


void scale_pix(t_all *all, char **map)
{
	int x;
	int y;
	int i;
	int j;

	y = -1;
	while (map[++y]) {
		x = -1;
		while (map[y][++x]) {
			if (map[y][x] == '1') {
				i = 0;
				while (i++ < SCALE) {
					my_mlx_pixel_put(all, x * SCALE + i, y * SCALE, 0x505050);
					j = 0;
					while (j++ < SCALE)
						my_mlx_pixel_put(all, x * SCALE + i, y * SCALE + j, 0x505050);
				}
			}

//			if (map[y][x] == '0') {
//				i = 0;
//				while (i++ < SCALE) {
//					my_mlx_pixel_put(img, x * SCALE + i, y * SCALE, 0x151515);
//					j = 0;
//					while (j++ < SCALE)
//						my_mlx_pixel_put(img, x * SCALE + i, y * SCALE + j, 0x151515);
//				}
//			}
		}
	}
}
void    init_img(t_all *all)
{
	all->win->img= mlx_new_image(all->win->mlx, all->textures.width, all->textures.height);
	all->win->addr = mlx_get_data_addr(all->win->img, &(all->win->bpp),&(all->win->line_l),
								  &(all->win->endian));
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