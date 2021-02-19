#include "./game/ft_game.h"
#include "./parser/ft_parser.h"


void draw_screen(t_all *all)
{
	t_cord ray;
	t_cord prev;
	int minus;
	t_cord tmp;



	char **map = all->map;


	double begin = -M_PI/6;
	double end = M_PI/6;

	init_img(all->win);
	scale_pix(all->win, map);
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);

	while (begin < end)
	{

		ray.x = all->plr.pos.x;
		ray.y = all->plr.pos.y;
tmp = all->plr.dir;
		all->plr.dir.x *= cos(begin);
		all->plr.dir.y *= sin(begin);

		while (!(is_wall_cord(map, ray)))
		{
			prev = ray;
			int col = 0xFFFF00;

//
			my_mlx_pixel_put(all->win, ray.x * SCALE, ray.y * SCALE, col);

			if (all->plr.dir.x == 1 && all->plr.dir.y == 0)//если луч кинут на право
				ray.x++;
			if (all->plr.dir.y == 1 && all->plr.dir.x == 0)//если луч кинут на лево
				ray.y++;
			else if (all->plr.dir.x > 0 && all->plr.dir.y > 0)//для iV части круга
			{
				ray.x = floor(ray.x + 1);//для иксов
				ray.y = ((ray.x - prev.x) / all->plr.dir.y) * all->plr.dir.x + prev.x;
				tmp.y = floor(ray.y + 1); //для игриков
				tmp.x = ((ray.y - prev.y) / all->plr.dir.x) * all->plr.dir.y + prev.y;
				if (tmp.x - ray.x < 0)
					ray = tmp;
			}


		}


		begin += 0.0025;
	}
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
		all->plr.pos.x -= 0.25;
	if (keycode == 'd')
		all->plr.pos.x += 0.25;
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
	all.plr.dir.x = 0.5;
	all.plr.dir.y = 1;

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
