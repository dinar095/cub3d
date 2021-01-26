#include <stdio.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"

int main()
{
	void *mlx = NULL;
	void *win = NULL;
	int x = 100;
	int y = 100;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "test");
	while (y++ < 200)
	{
		x = 100;
		while (x++ < 200)
		{
			mlx_pixel_put(mlx, win, x, y, 0xDC640A);
		}
	}
	mlx_loop(mlx);
	ft_putchar_fd('s', 1);
	return 0;
}
