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
int main(int argc, char **argv)
{
	int fd;
	char *line;
	int len;
	t_textures textures;
	reset_textures(&textures);
	len = 1;
	fd = open(argv[1], O_RDONLY);
	while (len && fd != -1)
	{
		len = get_next_line(fd, &line);
		parse_line(line, &textures);
		free(line);
	}
//	while (*(textures.map + len))
//	{
//		printf("%s\n", *(textures.map + len));
//		len++;
//	}
	check_valid(textures);
//	void *mlx = NULL;
//	void *win = NULL;
//	int x = 100;
//	int y = 100;
//
//	mlx = mlx_init();
//	win = mlx_new_window(mlx, 640, 480, "test");
//	while (y++ < 200)
//	{
//		x = 100;
//		while (x++ < 200)
//		{
//			mlx_pixel_put(mlx, win, x, y, 0xDC640A);
//		}
//	}
//	mlx_loop(mlx);
//	ft_putchar_fd('s', 1);
    close(fd);
	return 0;
}
