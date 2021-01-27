/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/01/27 15:20:58 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "../libft/libft.h"
#include "gnl/get_next_line.h"

void 	get_num_fromline(t_textures *textures, char **line)
{
	*line = *line + 2;
	textures->width = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	textures->height = ft_atoi(*line);
}

void 	get_char_fromline(t_textures *textures, char **line, char **texture)
{
	while (**line != '.' && (**line) + 1 != '/')
		(*line)++;
	*texture = ft_strdup(*line);
}

int		create_trgb(int t,int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	get_color_fromline(char **line, int **n)
{
	int r;
	int g;
	int b;
	unsigned long i;

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
	i = create_trgb(0, r, g, b);
	*n = ft_itoa_uhex(i);

}


void parse_line(char *line, t_textures *textures)
{

	if (!(ft_strncmp(line, "R ", 2)))
		get_num_fromline(textures, &line);
	else if (!(ft_strncmp(line, "NO", 2)))
		get_char_fromline(textures, &line, &(textures->no));
	else if (!(ft_strncmp(line, "SO", 2)))
			get_char_fromline(textures, &line, &(textures->so));
	else if (!(ft_strncmp(line, "WE", 2)))
			get_char_fromline(textures, &line, &(textures->we));
	else if (!(ft_strncmp(line, "EA", 2)))
			get_char_fromline(textures, &line, &(textures->ea));
	else if (!(ft_strncmp(line, "S ", 2)))
			get_char_fromline(textures, &line, &(textures->s));
	else if (!(ft_strncmp(line, "F ", 2)))
			get_color_fromline(&line, &(textures->f));
	else if (!(ft_strncmp(line, "C ", 2)))
			get_color_fromline(&line, &(textures->c));

}
int main(int argc, char **argv)
{
	int fd;
	char *line;
	int len;
	t_textures textures;

	len = 1;
	fd = open(argv[1], O_RDONLY);
	while (len)
	{
		len = get_next_line(fd, &line);
		parse_line(line, &textures);
		free(line);
	}
//	len = read_map(fd, &line);
//	textures = read_line(line);
//	//printf("%s\n", line);


}