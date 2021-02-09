/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/02/09 14:09:01 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"

void	reset_textures(t_textures *textures)
{
	textures->width = -1;
	textures->height = -1;
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->s = NULL;
	textures->f = -1;
	textures->c = -1;
	textures->map = NULL;
}

char 	**map_join(char ***map, char **line)
{
	char	**ret;
	size_t	i;
	size_t 	n;

	i = 0;
	n = -1;
	if (*map == NULL)
	{
		ret = (char **)malloc(sizeof(char *) + sizeof(char *));
		*ret = ft_strdup(*line);
		*(ret + 1) = NULL;
		return (ret);
	}
	while (*(*map + i) != NULL)
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));// выделилил память под 1 строку
	while (++n < i)//скопировать указатели строк в новое место
		*(ret + n) = *(*map + n);
	ret[n++] = ft_strdup(*line);
	ret[n] = NULL;
	free(*map);
	return (ret);
}

void	 get_map(t_textures *textures, char **line)
{
	if (!(check_header(textures)))
		return;
	if ((**line == '\n' || **line == '\0' || **line == '0') && textures->map == NULL)
		return;
	textures->map = map_join(&textures->map, line);
}

void	parse_line(char *line, t_textures *textures)
{

	if (!(ft_strncmp(line, "R ", 2)))
  		get_num_fromline(textures, &line);
	else if (!(ft_strncmp(line, "NO", 2)))
		get_char_fromline(&line, &(textures->no));
	else if (!(ft_strncmp(line, "SO", 2)))
			get_char_fromline(&line, &(textures->so));
	else if (!(ft_strncmp(line, "WE", 2)))
			get_char_fromline(&line, &(textures->we));
	else if (!(ft_strncmp(line, "EA", 2)))
			get_char_fromline(&line, &(textures->ea));
	else if (!(ft_strncmp(line, "S ", 2)))
			get_char_fromline(&line, &(textures->s));
	else if (!(ft_strncmp(line, "F ", 2)))
			get_color_fromline(&line, &(textures->f));
	else if (!(ft_strncmp(line, "C ", 2)))
			get_color_fromline(&line, &(textures->c));
	get_map(textures, &line);
}
