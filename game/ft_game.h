/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:02:47 by desausag          #+#    #+#             */
/*   Updated: 2021/04/06 20:51:13 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GAME_H
# define FT_GAME_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../parser/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <math.h>

# define SPD 0.49

# ifdef __linux__
# include "../linminilibx/mlx.h"
/*
** KEYCODES:
*/
#  define OS "LINUX"
#  define ESC 65307
#  define W 1731
#  define A 1734
#  define S 1753
#  define D 1751
#  define C 99
#  define UP 65362
#  define LEFT 65361
#  define DOWN 65364
#  define RIGHT 65363
#  define SPACE 32
# define X 33
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
# define X 17
# endif

typedef struct	s_chel
{
	double		x;
	double		y;
}				t_cord;
typedef struct	s_int
{
	int		i;
	int		j;
}				t_int;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	void		*mlx;
	void		*mlx_win;
	int			bpp;
	int			line_l;
	int			endian;
	int 		w;
	int			h;
	double 		y;
}               t_data;


typedef struct	s_plr //структура для игрока и луча
{
	t_cord		pos;
	t_cord		dir;
}				t_plr;

typedef struct	s_textures
{
	int			width;
	int			height;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f;
	int			c;
	char		**map;
	t_plr 		plr;
	t_cord		spr;
}				t_textures;
typedef struct s_sprite
{
	t_cord	pos;
	double	h;
	double	w;
	int 	cent;
	double 	dist;
	int 	co;//count
	int		vis;

}				t_sprite;
typedef struct	s_all // структура для всего вместе
{
	t_data		win;
	t_data		txre_img[5];
	t_plr		plr;
	char		**map;
	t_textures	textures;
	t_sprite 	*sprite;
	t_cord		ray0;
	int			save;
	t_cord		si_co;
}				t_all;

void			get_num_fromline(t_textures *textures, char **line);
void			get_char_fromline(char **line, char **texture);
int				create_trgb(int t, int r, int g, int b);
void			get_color_fromline(char **line, int *n);
int				check_header(t_textures *textures);
int				check_valid(t_textures textures);
int				open_file(char *file, t_textures *textures, t_all *all);
int				is_wall_cord(char **map,t_cord dot, t_cord ray);
void			scale_pix(t_all *all, char **map);
void			init_img(t_all *all);
double			ds_to_point(t_cord start, t_cord end);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
t_cord			crc(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b);
double			angle(t_cord begin, t_cord end);
t_cord			rotateZ(t_cord vector,double angle, t_cord si_co);
double			len_ray(t_cord ray1, t_cord ray2);
unsigned int	get_color(t_data txre_img, int x, int y);
t_cord			net_point(t_cord ray, t_cord pos);
void			init_texture(t_all *all);
t_cord			fwd_pnt(t_cord ray, t_cord pnt, int flag);
int				key_hook(int keycode, t_all *all);
void			draw_screen(t_all *all);
t_cord 			v_set(double val_x, double val_y);
t_cord			is_sprite(char **map,t_cord dot, t_cord ray);
void			null_sprites(t_all *all);
#endif //DESAUSAG_FT_GAME_H
