#include "./game/ft_game.h"
#include "./parser/ft_parser.h"

/*
** finds crossing dot of two NONPARALLEL vectors.
** It takes coordinates of two vectors, and of two dots
** lying on a line of the vectors.
** (from: https://habr.com/ru/post/523440/)
*/

t_cord   count_rays_cross(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b)//точка пересечения по точке и вектору
{
	t_cord dot_c;
	t_cord c;
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
//        if ((b.x + b.y * q) == 0)
//        {
//            write(0, "2", 1);
//        }
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
	t_cord tmp;
	tmp.x = (vector.x * cos(angle) - vector.y * sin(angle));

	tmp.y = (vector.x * sin(angle) + vector.y * cos(angle));

	return (tmp);
}
double len_ray(t_cord ray1, t_cord ray2)
{
	return (sqrt(pow(ray1.y - ray2.y, 2)) + pow(ray1.x - ray2.x, 2));
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
void draw_screen(t_all *all)
{
	t_cord ray;
	t_cord a;//вектор пользователя
	t_cord b_x = {0, 1};//вектор по x
	t_cord b_y = {1, 0};//вектор по y
	t_cord cross;
	t_cord cross_x;//вектор пересечения луча и х координаты
	t_cord cross_y;//вектор пересечения луч и у координаты
	t_cord dot_a;//точка на векторе пользователя
	t_cord dot_b;//точка на векторе сетки
	t_cord begin;//вектор поворота пользователя
	t_cord end;


	char **map = all->map;
	mlx_destroy_image(all->win->mlx, all->win->img);
	init_img(all->win);
	scale_pix(all->win, map);
	a = all->plr.dir;
	dot_a = all->plr.pos;


//	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);

//	my_mlx_pixel_put(all->win, cross_x.x * SCALE, cross_x.y * SCALE, 0xFFAA00);


	int col = 0xFFFF00;

	begin = rotateZ(a, 0);

	double angel = 0;

	while (angel < 0.785398)
	{
        end = rotateZ(begin, angel);
        dot_b = net_point(end, all->plr.pos);

		cross = all->plr.pos;


		while (!(is_wall_cord(map, cross, end)))
		{
                cross_x = count_rays_cross(end, b_x, dot_a, dot_b);//точка пересечения по х
                 cross_y = count_rays_cross(end, b_y, dot_a, dot_b);//точка пересечения по у
			if (len_ray(dot_a, cross_x) < len_ray(dot_a, cross_y))//если по х ближе чем по у
			{
				cross = cross_x;
				dot_b = fwd_pnt(end, dot_b, 1);
			}
			else //Если у ближе чем х
			{
				cross = cross_y;
                dot_b = fwd_pnt(end, dot_b, -1);
			}

            my_mlx_pixel_put(all->win, cross.x * SCALE, cross.y * SCALE, col);
          //  mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);

		}
		angel += 0.01;

	}

//	while (angel < 0.3)
//	{
//		dot_b.x = ceil(all->plr.pos.x);//работает для правой стороны
//		dot_b.y = ceil(all->plr.pos.y);
//		cross_y = count_rays_cross(rotateZ(begin, angel), b_y, dot_a, dot_b);
//
//		while (!(is_wall_cord(map, cross_y)))
//		{
//			//для вертикальных линий
//			cross_y = count_rays_cross(rotateZ(begin, angel), b_y, dot_a, dot_b);
//			dot_b.y++;
//			my_mlx_pixel_put(all->win, cross_y.x * SCALE, cross_y.y * SCALE, col);
//			mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
//		}
//		angel += 0.01;
//	}

	//my_mlx_pixel_put(all->win, dot_a.x * SCALE, dot_a.y * SCALE, col);

	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}


int             key_hook(int keycode, t_all *all)
{
   // printf("Keycode: %d\n", keycode);
    if (keycode == W)
		all->plr.pos.y -= 0.25;
	if (keycode == S)
		all->plr.pos.y += 0.25;
	if (keycode == A)
		all->plr.pos.x -= 0.25;
	if (keycode == D)
		all->plr.pos.x += 0.25;
	if (keycode == LEFT)
		all->plr.dir = rotateZ(all->plr.dir, -0.1);
	if (keycode == RIGHT)
		all->plr.dir = rotateZ(all->plr.dir, 0.1);
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

	all.plr.pos.x = 20.75;
	all.plr.pos.y = 1.75;
	all.plr.dir.x = 0.3;
	all.plr.dir.y = -0.6;

	all.win = &img;


	all.map = textures.map;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1300, 800, "Cub3d!");

    init_img(all.win);
	draw_screen(&all);

  //  mlx_key_hook(img.mlx_win, key_hook, &all);
    mlx_hook(all.win->mlx_win, 2, 1L<<0, key_hook, &all);


	mlx_loop(all.win->mlx);
	return 0;
}
