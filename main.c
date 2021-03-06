/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 20:50:44 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 20:59:09 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./game/ft_game.h"

int		chs_pnt(t_all *all, t_cord ray, t_cord *cross, t_cord *dot_b)
{
	t_cord	cross_x;
	t_cord	b_x;
	t_cord	b_y;
	int		side;

	b_x = v_set(0, 1);
	b_y = v_set(1, 0);
	cross_x = crc(ray, b_x, all->plr.pos, *dot_b);
	*cross = crc(ray, b_y, all->plr.pos, *dot_b);
	if (len_ray(all->plr.pos, cross_x) < len_ray(all->plr.pos, *cross))
	{
		side = 0;
		*cross = cross_x;
		*dot_b = fwd_pnt(ray, *dot_b, 1);
	}
	else
	{
		side = 1;
		*dot_b = fwd_pnt(ray, *dot_b, -1);
	}
	return (side);
}

void	clc_pnt(t_all *all, t_cord ray, double *zbuf)
{
	t_cord	cell;
	t_cord	cross;
	t_cord	dot_b;
	int		side;
	int		i;

	i = -1;
	while (++i < all->tx.width)
	{
		dot_b = net_point(ray, all->plr.pos);
		cross = all->plr.pos;
		while (!(is_wall_cord(all->map, cross, ray)))
		{
			side = chs_pnt(all, ray, &cross, &dot_b);
			if ((cell = is_sprite(all->map, cross, ray)).x != -1)
				init_sprite(all, cell);
		}
		zbuf[i] = print_wall(cross, all, v_int(i, side), ray);
		ray = rttz(ray, 0, all->si_co);
	}
}

int		draw_screen(t_all *all)
{
	t_cord		ray;
	double		*zbuf;

	zbuf = NULL;
	if (!(zbuf = (double *)malloc(sizeof(double) * all->tx.width)))
		err("Can't allocated");
	mlx_destroy_image(all->win.mlx, all->win.img);
	init_img(all);
	ray = rttz(all->plr.dir, -ANG / 2, all->si_co);
	all->ray0 = ray;
	null_sprites(all);
	clc_pnt(all, ray, zbuf);
	if (all->spr_co > 0)
		print_sprite(all, zbuf);
	if (zbuf != NULL)
		free(zbuf);
	if (all->save == 1)
		screen_image(all);
	mlx_put_image_to_window(all->win.mlx, all->win.mlx_win, all->win.img, 0, 0);
	return (0);
}

void	run(t_all *all)
{
	all->win.mlx = mlx_init();
	check_display_resolution(all);
	all->win.mlx_win = mlx_new_window(all->win.mlx, all->tx.width,
					all->tx.height, "Cub3d");
	init_texture(all);
	init_img(all);
	all->si_co = v_set(cos(ANG * (M_PI / 180) / all->tx.width),
					sin(ANG * (M_PI / 180) / all->tx.width));
	draw_screen(all);
	mlx_hook(all->win.mlx_win, 2, 1L << 0, k_prs, all);
	mlx_hook(all->win.mlx_win, 3, 1L << 1, k_rel, all);
	mlx_hook(all->win.mlx_win, X, 1L << 0, err, "0");
	mlx_loop_hook(all->win.mlx, key_hook, all);
	mlx_loop(all->win.mlx);
}

int		main(int argc, char **argv)
{
	t_tx		tx;
	t_all		all;

	all.save = 0;
	if (argc == 1 || (argc > 3 && check_ext(argv[1])))
		err("Invalid arguments\n");
	if (argc == 3)
	{
		if (!(ft_strncmp(argv[2], "--save", 7)))
			all.save = 1;
		else
			err("Invalid save argument");
	}
	open_file(argv[1], &tx, &all);
	run(&all);
	return (0);
}
