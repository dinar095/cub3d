/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 09:07:43 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 09:17:06 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_game.h"

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

void			check_display_resolution(t_all *all)
{
	int	wide;
	int	height;

	if (all->save == 0)
	{
		mlx_get_screen_size(all->win.mlx, &wide, &height);
		if (wide < all->tx.width)
			all->tx.width = wide;
		if (height < all->tx.height)
			all->tx.height = height;
	}
	else if (all->tx.width > 23000 || all->tx.height > 23000)
		err("Hello booly");
}
