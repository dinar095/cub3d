/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 09:10:12 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 09:11:46 by desausag         ###   ########.fr       */
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
	return (0);
}

void			init_img(t_all *all)
{
	all->win.img = mlx_new_image(all->win.mlx, all->tx.width,
								all->tx.height);
	all->win.addr = mlx_get_data_addr(all->win.img, &(all->win.bpp),
								&(all->win.line_l), &(all->win.endian));
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

unsigned int	vis(t_all *all, t_int s_t, t_cord cross, t_cord ray)
{
	int	tmp1;
	int	wall;

	wall = 0;
	tmp1 = 0;
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
