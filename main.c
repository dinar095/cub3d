/* ************************************************************************** *//*                                                                            *//*                                                        :::      ::::::::   *//*   main.c                                             :+:      :+:    :+:   *//*                                                    +:+ +:+         +:+     *//*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        *//*                                                +#+#+#+#+#+   +#+           *//*   Created: 2021/03/20 18:02:25 by desausag          #+#    #+#             *//*   Updated: 2021/03/21 20:17:26 by desausag         ###   ########.fr       *//*                                                                            *//* ************************************************************************** */#include "./game/ft_game.h"double	print_wall(t_cord plr,t_cord cross, t_textures textures, t_all *all, int x, t_cord ray, int side){	double d_to_wall;	double y0;	double y1;	double h;	double i;	unsigned int color;	double k;	int tmp1;	int tmp2;	int wall;	i = 0;	d_to_wall = len_ray(plr, cross) * angle(all->plr.dir, ray);	h = textures.height/(d_to_wall);  // line height	y0 = textures.height/2 - h/2;	y1 = textures.height/2 + h/2;	k = all->txre_img[side].h / h;	while (i <= textures.height)	{		if (i > y0  && i < y1) //смотрим по высоте		{			tmp2 = (int) (k * (i - y0));			if (side == 1)//NO&&SO			{				if (ray.y > 0)					wall = 1;				else					wall = 0;				tmp1 = (int)((cross.x - floor(cross.x)) * all->txre_img[wall].w);			}			else if (side == 0)//we ea			{				if (ray.x > 0)					wall = 3;				else					wall = 2;				tmp1 = (int)((cross.y - floor(cross.y)) * all->txre_img[wall].w);			}			color = get_color(all->txre_img[wall], tmp1, tmp2); //достать пиксель			my_mlx_pixel_put(all, x, i, color);		}		if (i <= y0)			my_mlx_pixel_put(all, x, i, 0xAFEEEE);		if (i >= y1)			my_mlx_pixel_put(all, x, i, 0xCD853F);		i++;	}	return (y0);}int is_sprite(char **map,t_cord dot, t_cord ray){	int x;	int y;	if (ray.x < 0)		x = (int)ceil(dot.x) - 1;	else		x =(int)dot.x;	if (ray.y <= 0)		y = (int)ceil(dot.y) - 1;	else		y = (int)dot.y;	if (map[y][x] == '2')		return 1;	else		return 0;}t_cord 			v_set(double val_x, double val_y){	t_cord		res;	res.x = val_x;	res.y = val_y;	return (res);}int sprite(t_cord cross, t_all *all, t_cord ray, float angel){	t_cord center;	t_cord sDir;	double r_x_s;	double len;	int i;	center.y = floor(cross.y) + 0.5;	center.x = floor(cross.x) + 0.5;	sDir = v_set(center.x - all->plr.pos.x, center.y - all->plr.pos.y);	r_x_s = acos(angle(sDir, all->plr.dir)) / (M_PI/180);	int q = (r_x_s / angel) * all->textures.width;	return q;//	sDir = rotateZ(all->plr.dir, 90);//	r_x_s = crc(sDir, ray, center, all->plr.pos);//	len = len_ray(r_x_s, center);//	i = (int)(len/(angel/all->textures.width));}void	draw_screen(t_all *all){	t_cord b_x = {0, 1};//вектор по x	t_cord b_y = {1, 0};//вектор по y	t_cord cross;	t_cord cross_x;//вектор пересечения луча и х координаты	t_cord dot_b;//точка на векторе сетки	t_cord ray;	double	zBuf[all->textures.width];	int i = 0;	char **map = all->map;	mlx_destroy_image(all->win->mlx, all->win->img);	init_img(all);	scale_pix(all, map);	int side;	float angel;	angel = 46;	ray = rotateZ(all->plr.dir, -angel/2);	while (i < all->textures.width)//привязать к ширине экрана	{        dot_b = net_point(ray, all->plr.pos);//точка пересечения сетки		cross = all->plr.pos;		while (!(is_wall_cord(map, cross, ray)))		{			cross_x = crc(ray, b_x, all->plr.pos, dot_b);//точка пересечения по х			cross = crc(ray, b_y, all->plr.pos, dot_b);//точка пересечения по у			if (len_ray(all->plr.pos, cross_x) < len_ray(all->plr.pos, cross))//если по х ближе чем по у			{				side = 0;				cross = cross_x;				dot_b = fwd_pnt(ray, dot_b, 1);			}			else //Если у ближе чем х			{				side = 1;                dot_b = fwd_pnt(ray, dot_b, -1);			}			my_mlx_pixel_put(all, cross.x * SCALE, cross.y * SCALE, 0xFF10100);			if (is_sprite(map, cross, ray))			{				sprite(all->textures.spr, all, ray, angel);			//на определенном х начинаем попадать в спрайт    cross			//находим центр этого спрайта  floor X;Y + 0.5			//кидаем от него перпендикулярный луч игроку tmp			//ищем точку пересечения ray и перпендикуляра			}		}		zBuf[i] = print_wall(all->plr.pos, cross, all->textures, all, i, ray, side);        ray = rotateZ(ray, (angel)/all->textures.width);		i++;	}	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);}int		main(int argc, char **argv) {    t_textures textures;    t_data img;    t_all all;    t_plr plr;    if (!open_file(argv[1], &textures))        return (0);    all.textures = textures;	all.plr = textures.plr;	all.win = &img;	all.map = textures.map;	img.mlx = mlx_init();	img.mlx_win = mlx_new_window(img.mlx, textures.width, textures.height, "Cub3d!");	init_texture(&all);    init_img(&all);	draw_screen(&all);   // mlx_key_hook(img.mlx_win, key_hook, &all); 	//mlx_loop_hook(all.win->mlx, draw_screen, all.win);    mlx_hook(all.win->mlx_win, 2, 1L<<0, key_hook, &all);	mlx_loop(all.win->mlx);	return 0;}