
#ifndef FT_GAME_H
# define FT_GAME_H
# include "../parser/ft_parser.h"
# include <math.h>

# define SCALE 5

# ifdef __linux__
# include "../linminilibx/mlx.h"
/*
** KEYCODES:
*/
#  define OS "LINUX"
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define C 99
#  define UP 65362
#  define LEFT 65361
#  define DOWN 65364
#  define RIGHT 65363
#  define SPACE 32
# else
#  include "../minilibx/mlx.h"
#  define OS "MAC"
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define C 8
#  define UP 126
#  define LEFT 123
#  define RIGHT 124
#  define DOWN 125
#  define SPACE 49
#  define LMOUSE 0
#  define RMOUSE 0
# endif

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

typedef struct		s_ray
{
    int				x;
    int				side;
    t_cord			dir;
    double			dist;
    double			perp;
    t_cord			cross;
   // t_sprite		*slist;
}					t_ray;

typedef struct	s_plr //структура для игрока и луча
{
	t_cord       pos;
	t_cord 		dir;
	float		start;
	float		end;
}				  t_plr;

typedef struct	s_all // структура для всего вместе
{
	t_data		*win;
	t_plr		plr;
	char		**map;
	t_textures textures;
}				  t_all;
int is_wall_cord(char **map,t_cord dot, t_cord ray);
int is_wall_point(char **map,double x,double y);
void scale_pix(t_data *img, char **map);
void    init_img(t_data *img);
double ds_to_point(t_cord start, t_cord end);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_cord   		crc(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b);
#endif //DESAUSAG_FT_GAME_H
