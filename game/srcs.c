#include "ft_game.h"
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x > 0 && y > 0) {
        dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
        *(unsigned int *) dst = color;
    }
    }

double ds_to_point(t_cord start, t_cord end)
{
	double xx = start.x - end.x;
	double yy = start.y - end.y;
	return sqrt(xx*xx + yy*yy);
}
//
//int is_wall_cord(char **map,t_cord dot, t_cord ray)
//{
//    int x;
//    int y;
//    if (ray.x > 0)
//    {
//        x = (int)dot.x;
//    }
//    else
//        x = (int)dot.x - 1;
//    if (ray.y > 0)
//        y = (int)dot.y;
//    else
//        y = (int)dot.y - 1;
//    if (map[y][x] != '1')
//        return 0;
//    else
//        return 1;
//}
int is_wall_cord(char **map,t_cord dot, t_cord ray)
{
    int x;
    int y;
    if (ray.x < 0)
        x = (int)ceil(dot.x) - 1;
    else
        x =(int)dot.x;
    if (ray.y <= 0)
        y = (int)ceil(dot.y) - 1;
    else
        y = (int)dot.y;

    if (map[y][x] != '1')
        return 0;
    else
        return 1;
}

int is_wall_point(char **map,double x,double y)
{
	t_cord ray = {x, y};

	if (map[(int) ray.y][(int) ray.x] != '1')
		return 0;
	else
		return 1;
}


void scale_pix(t_data *img, char **map)
{
	int x;
	int y;
	int i;
	int j;

	y = -1;
	while (map[++y]) {
		x = -1;
		while (map[y][++x]) {
			if (map[y][x] == '1') {
				i = 0;
				while (i++ < SCALE) {
					my_mlx_pixel_put(img, x * SCALE + i, y * SCALE, 0x505050);
					j = 0;
					while (j++ < SCALE)
						my_mlx_pixel_put(img, x * SCALE + i, y * SCALE + j, 0x505050);
				}
			}

//			if (map[y][x] == '0') {
//				i = 0;
//				while (i++ < SCALE) {
//					my_mlx_pixel_put(img, x * SCALE + i, y * SCALE, 0x151515);
//					j = 0;
//					while (j++ < SCALE)
//						my_mlx_pixel_put(img, x * SCALE + i, y * SCALE + j, 0x151515);
//				}
//			}
		}
	}
}
void    init_img(t_data *img)
{
	img->img= mlx_new_image(img->mlx, 1300, 800);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),&(img->line_l),
								  &(img->endian));
}
