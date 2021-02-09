#include <stdio.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "parser/ft_parser.h"
int check_map_wide(char **map, int i, int j)
{
    int t;
    int flag;

    flag = 0;
    t = j;
    while (flag == 0 && map[i][t])
    {
        if (map[i][t] == '1')
            flag = 2;
        t++;
    }
    t = j;
    while (t >= 0 && flag == 2 && map[i][t])
    {
        if (map[i][t] == '1')
            flag = 1;
        t--;
    }
    return (flag == 1 ? 1 : 0);
}
int check_map_height(char **map, int i, int j)
{
    int t;
    int flag;
    int len;

    flag = 0;
    t = i;
    len = 1;
    while (t >= 0 && flag == 0 && len)
    {
        if (map[t][j] == '1')
            flag = 2;
        if (t > 0)
            len = (ft_strlen(map[t - 1]) >= j ? 1 : 0);
        else if (t == 0)
            len = (ft_strlen(map[t]) >= j ? 1 : 0);
        t--;
    }
    len = 1;
    while (flag == 2 && map[i] && len)
    {
        if (map[i][j] == '1')
            flag = 1;
        if (map[i + 1])
            len = (ft_strlen(map[i + 1]) >= j ? 1 : 0);
        else if (!(map[i + 1]))
            len = (ft_strlen(map[i]) >= j ? 1 : 0);
        i++;
    }
    return (flag == 1 ? 1 : 0);
}
int	check_valid(t_textures textures)
{
	char **map;
	int i;
	int j;
	int flag;
	flag = 1;

	i = 0;
	map = textures.map;
	// сделать проверку на 1 строку и 1 столбец
    while (flag == 1 && map[i])//проверяем построчно верность
    {
        j = 0;
        while (flag == 1 && map[i][j])
        {
            if (map[i][j] == '0')
            {
                flag = check_map_wide(map, i, j);//Если на какой-то строке флаг = 0, то выходим из цикла
                if (flag)
                    flag = check_map_height(map, i, j);
            }
            j++;
        }
        i++;
    }
	printf("line %d: '%s'\n",i-1, map[i-1]);
    printf("char %d: %c\n",j, map[i-1][j]);
    printf("%d\n", flag);
    return (flag);


}
typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

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

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				my_mlx_pixel_put(img, x, y, 0x00FF0000);
			}
			x++;
		}
		y++;
	}
}
int main(int argc, char **argv)
{
	int fd;
	char *line;
	int len;
	t_textures textures;
	reset_textures(&textures);
	len = 1;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("Eroor map.", 1);
		return (0);
	}
	while (len && fd != -1)
	{
		len = get_next_line(fd, &line);
		parse_line(line, &textures);
		free(line);
	}
	if (!(check_valid(textures)))
		return (0);

	void    *mlx;
	void    *mlx_win;
	t_data  img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 600, "Hello world!");
	img.img = mlx_new_image(mlx, 600, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	int x;
	int y = 0;
	char **map = textures.map;

	scale_pix(&img, 16, map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	ft_putchar_fd('s', 1);
    close(fd);
	return 0;
}
