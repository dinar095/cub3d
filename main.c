#include <stdio.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "parser/ft_parser.h"
#include <math.h>
#define SCALE 16
typedef struct  s_data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct	s_win //структура для окна
{
    void		*mlx;
    void		*win;
    void		*img;
    void		*addr;
    int			line_l;
    int			bpp;
    int			en;
}				  t_win;

typedef struct	s_plr //структура для игрока и луча
{
    float		x;
    float		y;
    float		dir;
    float		start;
    float		end;
}				  t_plr;

typedef struct	s_all // структура для всего вместе
{
    t_win		*win;
    t_plr		*plr;
    char		**map;
}				  t_all;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void scale_pix(t_data *img, int scale, char **map)
{
	int x;
	int y;
    int i;
    int j;

    y = -1;
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
            if (map[y][x] == '1')
            {
                i = 0;
                while (i++ < scale)
                {
                    my_mlx_pixel_put(img, x * scale + i, y * scale, 0x00FF0000);
                    j = 0;
                    while (j++ < scale)
                        my_mlx_pixel_put(img, x * scale + i, y * scale + j, 0x00FF0000);
                }
            }
    }
}
void	ft_cast_ray(t_all *all)
{
    t_plr	ray = *all->plr; // задаем координаты луча равные координатам игрока

    while (all->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
    {
        ray.x += cos(ray.dir);
        ray.y += sin(ray.dir);
        mlx_pixel_put(all->mlx, all->win, ray.x, ray.y, 0x990099);
    }
}
int main(int argc, char **argv)
{
	t_textures textures;
	if (!open_file(argv[1], &textures))
        return (0);

	void    *mlx;
	void    *mlx_win;
	t_data  img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	char **map = textures.map;
	scale_pix(&img, 40, map);



    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return 0;
}
