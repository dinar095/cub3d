/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:56:06 by desausag          #+#    #+#             */
/*   Updated: 2021/01/26 18:52:30 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


typedef struct s_textures
{
	int		width;
	int		height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int 	f;
	int 	c;
	char	**map;
}				t_textures;
#endif
