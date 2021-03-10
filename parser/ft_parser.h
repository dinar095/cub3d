/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:56:06 by desausag          #+#    #+#             */
/*   Updated: 2021/03/10 18:28:14 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "gnl/get_next_line.h"
# include "../libft/libft.h"

typedef struct	s_textures
{
	int		width;
	int		height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		f;
	int		c;
	char	**map;
}				t_textures;
void			get_num_fromline(t_textures *textures, char **line);
void			get_char_fromline(char **line, char **texture);
int				create_trgb(int t, int r, int g, int b);
void			get_color_fromline(char **line, int *n);
int				check_header(t_textures *textures);
int             check_valid(t_textures textures);
int             open_file(char *file, t_textures *textures);
#endif
