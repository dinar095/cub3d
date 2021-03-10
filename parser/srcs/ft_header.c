/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:45:56 by desausag          #+#    #+#             */
/*   Updated: 2021/03/10 18:28:14 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_parser.h"

void	get_num_fromline(t_textures *textures, char **line)
{
	*line = *line + 2;
	textures->width = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	textures->height = ft_atoi(*line);
}

void	get_char_fromline(char **line, char **texture)
{
	while (**line != '.' && (**line) + 1 != '/')
		(*line)++;
	*texture = ft_strdup(*line);
}

int		create_trgb(int t,int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	get_color_fromline(char **line, int *n)
{
	int r;
	int g;
	int b;

	*line = *line + 2;
	r = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	(*line)++;
	g = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	(*line)++;
	b = ft_atoi(*line);
	*n = create_trgb(0, r, g, b);
}
int 	check_header(t_textures *textures)
{
	int i;

	i = 0;
	if (textures->width > 0 && textures->height > 0)
		i++;
	if (textures->f > -1 && textures->c > -1)
		i++;
	if (textures->no && textures->so && textures->we && textures->ea)
		i++;
	if (textures->s)
		i++;
	return (i == 4 ? 1 : 0);
}
