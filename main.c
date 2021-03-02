#include "./game/ft_game.h"
#include "./parser/ft_parser.h"

/*
** finds crossing dot of two NONPARALLEL vectors.
** It takes coordinates of two vectors, and of two dots
** lying on a line of the vectors.
** (from: https://habr.com/ru/post/523440/)
*/

t_cord   count_rays_cross(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b)
{
	t_cord dot_c;
	t_cord c;
	double  q;
	double  n;

	ft_bzero(&dot_c, sizeof(t_cord));
	if (a.y != 0)
	{
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
	return (sqrt(pow(ray2.y - ray1.y, 2)) + pow(ray2.x - ray1.x, 2));
}

void draw_screen(t_all *all)
{
	t_cord ray;
	t_cord a;
	t_cord b_x = {0, 1};
	t_cord b_y = {1, 0};
	t_cord cross;
	t_cord cross_x;
	t_cord cross_y;
	t_cord dot_a;
	t_cord dot_b;
	t_cord begin;
	t_cord end;


	char **map = all->map;

	init_img(all->win);
	scale_pix(all->win, map);
	a = all->plr.dir;
	dot_a = all->plr.pos;


	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);

	my_mlx_pixel_put(all->win, cross_x.x * SCALE, cross_x.y * SCALE, 0xFFAA00);


	int col = 0xFFFF00;

	begin = rotateZ(a, 0);
	end = a;

	double angel = 0;
	double r1;
	double r2;
	while (angel < 0.785398)
	{
		dot_b.x = ceil(all->plr.pos.x);//работает для правой стороны
		dot_b.y = ceil(all->plr.pos.y);
		cross = count_rays_cross(rotateZ(begin, angel), b_x, dot_a, dot_b);

		while (!(is_wall_cord(map, cross)))
		{
			//для вертикальных линий
			cross_x = count_rays_cross(rotateZ(begin, angel), b_x, dot_a, dot_b);
			cross_y = count_rays_cross(rotateZ(begin, angel), b_y, dot_a, dot_b);
			if (len_ray(dot_a, cross_x) < len_ray(dot_a, cross_y))
			{
				cross = cross_x;
				dot_b.x++;
			}
			else if (len_ray(dot_a, cross_x) > len_ray(dot_a, cross_y))
			{
				cross = cross_y;
				dot_b.y++;
			}

			my_mlx_pixel_put(all->win, cross.x * SCALE, cross.y * SCALE, col);
			mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
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

	my_mlx_pixel_put(all->win, dot_a.x * SCALE, dot_a.y * SCALE, col);

	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}


int             key_hook(int keycode, t_all *all)
{
    printf("Keycode: %C\n", keycode);
    if (keycode == 'w')
		all->plr.pos.y -= 0.25;
	if (keycode == 's')
		all->plr.pos.y += 0.25;
	if (keycode == 'a')
		all->plr.dir = rotateZ(all->plr.dir, -0.1);
	if (keycode == 'd')
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

	all.plr.pos.x = 15.75;
	all.plr.pos.y = 10.75;
	all.plr.dir.x = 0.1;
	all.plr.dir.y = 0.6;

	all.win = &img;


	all.map = textures.map;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1300, 800, "Cub3d!");

	draw_screen(&all);

  //  mlx_key_hook(img.mlx_win, key_hook, &all);
    mlx_hook(all.win->mlx_win, 2, 1L<<0, key_hook, &all);


	mlx_loop(all.win->mlx);
	return 0;
}
