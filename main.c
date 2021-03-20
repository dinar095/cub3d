#include "./game/ft_game.h"


double len_ray(t_cord ray1, t_cord ray2)
{
	return (sqrt(pow(ray1.y - ray2.y, 2) + pow(ray1.x - ray2.x, 2)));
}
//void         drop_rays(t_all *all)
//{
//    t_ray      ray;
//    double      cam;
//
//    ray.x = 0;
//    while (ray.x < all->textures.width)
//    {
//        //ray.slist = NULL;
//        cam = 2 * ray.x / (double)all->textures.width - 1;
//        ray.dir.x = all->plr.dir.x + cam * all->plr.dir.x;
//        ray.dir.y = all->plr.dir.y + cam * all->plr.dir.y;
//        count_ray_len(all, &ray);//ПУскаем луч
//        ray.perp = ray.dist * v_mult(ray.dir, all->player.dir)/v_len(all->player.dir) / v_len(ray.dir);//Избавляемся от фишай
//        draw_strip(all, &ray);//
//        ray.x++;
//    }
//    draw_sprites(all);
//}
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
void print_wall(t_cord plr,t_cord cross, t_textures textures, t_all *all, int x, t_cord ray, int side)
{
	double d_to_wall;
	double y0;
	double y1;
	double h;
	double i;
	unsigned int color;
	double k;
	int tmp1;
	int tmp2;

	printf("%d\n", side);
	i = 0;
	d_to_wall = len_ray(plr, cross) * angle(all->plr.dir, ray);

	h = textures.height/(d_to_wall);  // line height
	y0 = textures.height/2 - h/2;
	y1 = textures.height/2 + h/2;
	k = all->txre_img[side].h / h;
	while (i <= textures.height)
	{
		if (i >= y0  && i <= y1) //смотрим по высоте
		{
			if (side == 1)
			{
				tmp1 = (int) ((cross.x - floor(cross.x)) * all->txre_img[side].w);
				tmp2 = (int) (k * (i - y0));
			}
			else if (side == 0)
			{
				tmp1 = (int) ((cross.y - floor(cross.y)) * all->txre_img[side].w);
				tmp2 = (int) (k * (i - y0));
			}
			color = get_color(all->txre_img[side], tmp1, tmp2); //достать пиксель
			my_mlx_pixel_put(all, x, i, color);
		}
		if (i < y0)
			my_mlx_pixel_put(all, x, i, 0xAFEEEE);
		if (i > y1)
			my_mlx_pixel_put(all, x, i, 0xCD853F);
//		else
//			my_mlx_pixel_put(all, x, i, 0x00bfff);
		i++;
	}

//	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}
void init_texture(t_all *all)
{
	all->txre_img[0].img = mlx_xpm_file_to_image(all->win->mlx, all->textures.no, &all->txre_img[0].w, &all->txre_img[0].h);

	all->txre_img[1].img = mlx_xpm_file_to_image(all->win->mlx, all->textures.so, &all->txre_img[1].w, &all->txre_img[1].h);
}//need free pa

void draw_screen(t_all *all)
{
	t_cord b_x = {0, 1};//вектор по x
	t_cord b_y = {1, 0};//вектор по y
	t_cord cross;
	t_cord cross_x;//вектор пересечения луча и х координаты

	t_cord dot_b;//точка на векторе сетки

	t_cord ray;
	int i = 0;

	char **map = all->map;
	mlx_destroy_image(all->win->mlx, all->win->img);
	init_img(all);
	scale_pix(all, map);
	int side;
	float angel;
	angel = 46;
	ray = rotateZ(all->plr.dir, -angel/2);
	while (i < all->textures.width)//привязать к ширине экрана
	{

        dot_b = net_point(ray, all->plr.pos);//точка пересечения сетки
		cross = all->plr.pos;
		while (!(is_wall_cord(map, cross, ray)))
		{
                cross_x = crc(ray, b_x, all->plr.pos, dot_b);//точка пересечения по х
                cross = crc(ray, b_y, all->plr.pos, dot_b);//точка пересечения по у
			if (len_ray(all->plr.pos, cross_x) < len_ray(all->plr.pos, cross))//если по х ближе чем по у
			{
				side = 0;
				cross = cross_x;
				dot_b = fwd_pnt(ray, dot_b, 1);
			}
			else //Если у ближе чем х
			{
				side = 1;
                dot_b = fwd_pnt(ray, dot_b, -1);
			}
			my_mlx_pixel_put(all, cross.x * SCALE, cross.y * SCALE, 0xFF10100);
		}
		print_wall(all->plr.pos, cross, all->textures, all, i, ray, side);
        ray = rotateZ(ray, (angel)/all->textures.width);
		i++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}


int             key_hook(int keycode, t_all *all)
{
   // printf("Keycode: %d\n", keycode);
   t_cord tmp;
   t_cord nDir;
    if (keycode == W || keycode == S)
	{
    	if (keycode == W)
    	{
			tmp.x = all->plr.pos.x + all->plr.dir.x * 0.5;
			tmp.y = all->plr.pos.y + all->plr.dir.y * 0.5;
		}
    	else
		{
			tmp.x = all->plr.pos.x - all->plr.dir.x * 0.5;
			tmp.y = all->plr.pos.y - all->plr.dir.y * 0.5;
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
		tmp.x = all->plr.pos.x + nDir.x * 0.5;
		tmp.y = all->plr.pos.y + nDir.y * 0.5;
		if (!(is_wall_cord(all->map, tmp, nDir)))
			all->plr.pos = tmp;
	}
	if (keycode == LEFT)
		all->plr.dir = rotateZ(all->plr.dir, -5);
	if (keycode == RIGHT)
		all->plr.dir = rotateZ(all->plr.dir, 5);
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
//	mlx_hook(all->win->mlx_win, 2, 1L<<0, key_hook, &all);
    draw_screen(all);
}

int main(int argc, char **argv) {
    t_textures textures;
    t_data img;
    t_all all;
    t_plr plr;
    if (!open_file(argv[1], &textures))
        return (0);
    all.textures = textures;

	all.plr.pos.x = 10;
	all.plr.pos.y = 5;
	all.plr.dir.x = 0;
	all.plr.dir.y = -1;

	all.win = &img;


	all.map = textures.map;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, textures.width, textures.height, "Cub3d!");
	init_texture(&all);
    init_img(&all);
	draw_screen(&all);

   // mlx_key_hook(img.mlx_win, key_hook, &all);
 	//mlx_loop_hook(all.win->mlx, draw_screen, all.win);
    mlx_hook(all.win->mlx_win, 2, 1L<<0, key_hook, &all);


	mlx_loop(all.win->mlx);
	return 0;
}
