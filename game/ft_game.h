
#ifndef FT_GAME_H
# define FT_GAME_H
# include "../parser/ft_parser.h"
# include <math.h>
# include "../minilibx/mlx.h"
# define SCALE 40
typedef struct s_chel
{
	double x;
	double y;
}               t_cord;

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
int is_wall_cord(char **map,t_cord ray);
int is_wall_point(char **map,double x,double y);
void scale_pix(t_data *img, char **map);
void    init_img(t_data *img);
double ds_to_point(t_cord start, t_cord end);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif //DESAUSAG_FT_GAME_H
