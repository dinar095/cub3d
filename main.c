#include "./game/ft_game.h"
#include "./parser/ft_parser.h"


//

void draw_screen(t_all *all)
{
	t_cord ray;
	t_cord ray_prev;
	int minus;
	t_cord tmp;
	float dir = all->plr->dir;



	char **map = all->map;

	ray_prev.x = all->plr->pos.x;
	ray_prev.y = all->plr->pos.y;


	float dbegin = dir - 1;
	float end = dir + 3;

	init_img(all->win);
	scale_pix(all->win, map);

	while (dbegin < end)
	{
		ray.x = all->plr->pos.x;
		ray.y = all->plr->pos.y;

		while (!(is_wall_cord(map, ray)))
		{
			int col = 0xFFFF00;
			my_mlx_pixel_put(all->win, ray.x * SCALE, ray.y * SCALE, col);

			ray_prev.x = ray.x;
			ray_prev.y = ray.y;

double k = ray.y - ray_prev.y;

			ray.y = k * (floor(ray.x + 1) - ray_prev.x)/(ray.x - ray_prev.x) + ray_prev.y;
			ray.x = floor(ray.x + 1);
//				float b = ray.y - (dbegin *	ray.x);
//				ray.x = (floor(ray_prev.x + 1));
//				ray.y = dbegin * ray.x + b;
//				tmp.y = floor(ray_prev.y + 1);
//				tmp.x = (tmp.y - b)/dbegin;
//				if (ray.x - tmp.x >= 0)
//				{
//					ray.x = tmp.x;
//					ray.y = tmp.y;
//				}
		}

		dbegin += 0.01;
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
		all->plr->dir -= 0.25;
	if (keycode == 'd')
		all->plr->dir += 0.25;
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
	all.plr->dir = 1;

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
