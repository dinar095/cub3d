/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:02:47 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 20:21:18 by desausag         ###   ########.fr       */
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

# define SPD 0.19
# define ANG 46

# ifdef __linux__
#  include "../libmlx_lin/mlx.h"
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
#  define X 33
# else
#  include "../libmlx_mac/mlx.h"
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
#  define X 17
# endif

typedef struct	s_chel
{
	double		x;
	double		y;
}				t_cord;

typedef struct	s_int
{
	int			i;
	int			j;
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
	int			w;
	int			h;
	double		y;
}				t_data;

typedef struct	s_plr
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
	t_plr		plr;
	t_cord		spr;
}				t_tx;

typedef struct	s_sprite
{
	t_cord		pos;
	double		h;
	int			cent;
	double		dist;
	int			vis;
}				t_sprite;

typedef struct	s_all
{
	t_data		win;
	t_data		txre_img[5];
	t_plr		plr;
	char		**map;
	t_tx		tx;
	t_sprite	*sp;
	t_cord		ray0;
	int			save;
	t_cord		si_co;
	int			spr_co;
}				t_all;

unsigned int	get_color(t_data txre_img, int x, int y);
t_cord			crc(t_cord a, t_cord b, t_cord dot_a, t_cord dot_b);
t_cord			rttz(t_cord vector, double angle, t_cord si_co);
t_cord			net_point(t_cord ray, t_cord pos);
t_cord			fwd_pnt(t_cord ray, t_cord pnt, int flag);
t_cord			v_set(double val_x, double val_y);
t_cord			is_sprite(char **map, t_cord dot, t_cord ray);
double			len_ray(t_cord ray1, t_cord ray2);
double			angle(t_cord begin, t_cord end);
double			print_wall(t_cord crs, t_all *all, t_int x_s, t_cord ray);
t_int			v_int(int val_x, int val_y);
void			get_num_fromline(t_tx *tx, char **line);
void			get_color_fromline(char **line, int *n);
void			get_char_fromline(char **line, char **texture);
void			h_err(t_tx *tx);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
void			init_img(t_all *all);
void			init_texture(t_all *all);
void			null_sprites(t_all *all);
int				err(char *s);
void			sort_sprite(t_all *all);
void			print_sprite(t_all *all, double *zbuf);
void			draw_sprite(t_all *all, t_sprite spr, double *zbuf);
void			init_sprite(t_all *all, t_cord cross);
void			check_display_resolution(t_all *all);
void			screen_image(t_all *all);
int				create_trgb(int t, int r, int g, int b);
int				check_header(t_tx *tx);
int				check_valid(t_tx tx);
int				open_file(char *file, t_tx *tx, t_all *all);
int				is_wall_cord(char **map, t_cord dot, t_cord ray);
int				key_hook(int keycode, t_all *all);
int				draw_screen(t_all *all);
int				check_ext(const char *f_name);
#endif
