#include "./game/ft_game.h"
#include "./parser/ft_parser.h"

void wall_270_0()

void draw_screen(t_all *all)
{
	t_cord ray;
	t_cord ray_prev;
	int minus;
	t_cord tmp;



	char **map = all->map;

	ray_prev.x = all->plr->pos.x;
	ray_prev.y = all->plr->pos.y;

	double alpha = M_PI;//0.1
	double c = 0.5;

	double begin = alpha - M_PI;
	double end = alpha + M_PI;

	init_img(all->win);
	scale_pix(all->win, map);
	double ll = (floor(ray.y + 1) - ray.y);
	while (begin < end)
	{
//		minus = 1;
//		if (ray_prev.y - ray.y < 0 )
		ray.x = all->plr->pos.x;
		ray.y = all->plr->pos.y;

		while (!(is_wall_cord(map, ray)))
		{
			int col = 0xFFFF00;
//
			my_mlx_pixel_put(all->win, ray.x * SCALE, ray.y * SCALE, col);

			ray_prev.x = ray.x;
			ray_prev.y = ray.y;

			ray.x += c * cos(begin);
			ray.y += c * sin(begin);
			double k = (ray.y - ray_prev.y)/(ray.x - ray_prev.x);
			if (k != 0)
			{
				double b = ray.y - (k *	ray.x);
				ray.x = (floor(ray_prev.x + 1));
				ray.y = k * ray.x + b;
				tmp.y = floor(ray_prev.y + 1);
				tmp.x = (tmp.y - b)/k;
				if (ray.x - tmp.x >= 0)
				{
					ray.x = tmp.x;
					ray.y = tmp.y;
				}
			}
		}

		begin += 0.025;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->mlx_win, all->win->img, 0, 0);
}

int             key_hook(int keycode, t_all *all)
{
    printf("Keycode: %C\n", keycode);
    if (keycode == 'w')
    	all->plr->pos.y -= 0.25;
	if (keycode == 's')
		all->plr->pos.y += 0.25;
	if (keycode == 'a')
		all->plr->pos.x -= 0.25;
	if (keycode == 'd')
		all->plr->pos.x += 0.25;
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

	all.plr->pos.x = 15.75;
	all.plr->pos.y = 10.75;

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
