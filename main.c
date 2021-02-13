#include <stdio.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "parser/ft_parser.h"
#include <math.h>
#define SCALE 40
typedef struct  s_data
{
	void        *img;
	char        *addr;
	void        *mlx;
	void        *mlx_win;
	int         bpp;
	int         line_l;
	int         endian;
}               t_data;


typedef struct s_chel
{
    double x;
    double y;
}               t_cord;

typedef struct	s_plr //структура для игрока и луча
{
   t_cord       pos;
    float		dir;
    float		start;
    float		end;
}				  t_plr;

typedef struct	s_all // структура для всего вместе
{
    t_data		*win;
    t_plr		*plr;
    char		**map;
}				  t_all;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

double ds_to_point(t_cord start, t_cord end)
{
    double xx = start.x - end.x;
    double yy = start.y - end.y;
    return sqrt(xx*xx + yy*yy);
}

int is_wall_cord(char **map,t_cord ray)
{
    if (map[(int) ray.y][(int) ray.x] != '1')
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

            if (map[y][x] == '0') {
                i = 0;
                while (i++ < SCALE) {
                    my_mlx_pixel_put(img, x * SCALE + i, y * SCALE, 0x151515);
                    j = 0;
                    while (j++ < SCALE)
                        my_mlx_pixel_put(img, x * SCALE + i, y * SCALE + j, 0x151515);
                }
            }
        }
    }
}
void    init_img(t_data *img, char **map)
{
    img->mlx = mlx_init();
    img->mlx_win = mlx_new_window(img->mlx, 1300, 800, "Hello world!");
    img->img= mlx_new_image(img->mlx, 1300, 800);
    img->addr = mlx_get_data_addr(img->img, &(img->bpp),&(img->line_l),
                                 &(img->endian));
    scale_pix(img, map);
}
int main(int argc, char **argv)
{
	t_textures textures;
    t_data  img;
	if (!open_file(argv[1], &textures))
        return (0);
    init_img(&img, textures.map);

    t_cord ray;
    t_cord ray_prev;
    t_cord cam;

    cam.x = 15.75;
    cam.y = 10.3;
    my_mlx_pixel_put(&img, cam.x * SCALE, cam.y * SCALE, 0xFFFF00);

    ray.x = cam.x;
    ray.y = cam.y;

    ray_prev.x = ray.x;
    ray_prev.y = ray.y;

    double alpha = M_PI;//0.1
    double c = 0.1;

    double begin = alpha - M_PI;
    double end = alpha + M_PI;
    char **map = textures.map;
    while (begin < end)
    {
        ray.x = cam.x;
        ray.y = cam.y;
        while (!(is_wall_cord(map, ray)))
        {



            if ((ceil(ray.x) - ceil(ray_prev.x))>=1) // проверка по x
            {
                if ((is_wall_point(map,ray.x-1,ray.y))) {
                    my_mlx_pixel_put(&img, ray.x * SCALE, ray.y * SCALE, 0xFF0000);
                    break;
                }
            }

            if ((ceil(ray.y) - ceil(ray_prev.y))>=1) // проверка по y
            {
                if ((is_wall_point(map,ray.x,ray.y-1))) {
                    my_mlx_pixel_put(&img, ray.x * SCALE, ray.y * SCALE, 0xFF00FF);
                    break;
                }
            }
            my_mlx_pixel_put(&img, ray.x * SCALE, ray.y * SCALE, 0xCCCC00);

            ray_prev.x = ray.x;
            ray_prev.y = ray.y;
            ray.x += c * cos(begin);
            ray.y += c * sin(begin);

        }
        //my_mlx_pixel_put(&img, ray.x * SCALE, ray.y * SCALE, 0x00FFFF);




        begin += 0.015;

    }


    mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_loop(img.mlx);
	return 0;
}
