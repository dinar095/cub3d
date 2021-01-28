/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/01/28 15:36:23 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "../libft/libft.h"
#include "gnl/get_next_line.h"
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
char	**map_join(char ***map, char **line)
{
	char	**ret;
	size_t	i;
	size_t 	n;

	i = 0;
	n = 0;
//	if (!map || !line)
//		return (NULL);
//	if (*map == NULL)
//	{
//		*map = (char **)malloc(sizeof(char *) + sizeof(char *));
//		*map = ft_strdup(*line);
//		*(map + 1) = NULL;
//		printf("%s\n", **map);
//	}
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
	while (n < i)//скопировать указатели строк в новое место
	{
		*(ret + n) = *(*map + n);
		n++;
	}
	ret[n++] = ft_strdup(*line);
	ret[n] = NULL;
	free(*map);
	printf("%s\n", ret[n-1]);
	return (ret);
}
void get_map(t_textures *textures, char **line)
{
	int i;
	char **tmp;

	i = 0;
	if (!(i = check_header(textures)))
		return;
	if (**line == '\n' || **line == '\0' || **line == '0')
		return;
	textures->map = map_join(&textures->map, line);
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
	get_map(textures, &line);

}
int main(int argc, char **argv)
{
	int fd;
	char *line;
	int len;
	t_textures textures;
	reset_textures(&textures);
	len = 1;
	fd = open(argv[1], O_RDONLY);
	while (len)
	{
		len = get_next_line(fd, &line);
		parse_line(line, &textures);
		free(line);
	}
//	while (len < 50)
//	{
//		printf("%s\n", *(textures.map + len));
//		len++;
//	}


}