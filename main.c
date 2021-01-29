#include <stdio.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "parser/ft_parser.h"

int	check_valid(t_textures textures)
{
	char **map;
	int i;
	int j;
	int flag;
	flag = 1;

	i = 0;
	map = textures.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == '0')//проверка в ширину
			{

			}
		}
	}
	printf("%s\n", map[0]);
	printf("%s\n", map[4]);
	printf("%c\n", map[4][1]);


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
//	while (len < 15)
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
	return 0;
}
