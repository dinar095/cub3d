/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:02:36 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 09:11:46 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

double			len_ray(t_cord ray1, t_cord ray2)
{
	return (sqrt(pow(ray1.y - ray2.y, 2) + pow(ray1.x - ray2.x, 2)));
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

void			null_sprites(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->spr_co)
		all->sp[i].vis = 0;
}

int				err(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	exit(1);
	return (1);
}
