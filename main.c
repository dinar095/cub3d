#include <stdio.h>
#include "minilibx/mlx.h"
#include "libft/libft.h"

int main()
{
	void *mlx = NULL;
	void *win = NULL;
	int x = -1;
	int y = -1;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "test");
	mlx_loop(mlx);
ft_putchar_fd('s', 1);
	return 0;
}
