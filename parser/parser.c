/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/01/26 19:11:30 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parser.h"
#include "../libft/libft.h"
#include "gnl/get_next_line.h"

//int read_map(int  fd, char **line)
//{
//	char buf[501];
//	char *tmp;
//	int count;
//	int len;
//
//	len = 0;
//	if ((read(fd, NULL, 0) == -1) || !line)
//		return (-1);
//	*line = ft_strdup("");
//	while ((count = read(fd, buf, 500)))
//	{
//		buf[count] = '\0';
//		len += count;
//		tmp = *line;
//		*line = ft_strjoin(tmp, buf);
//		free(tmp);
//	}
//	return (len);
//}
//char	*get_next_line(char **line)
//{
//	char *ptr;
//	char *tmp;
//
//	ptr = NULL;
//	if ((ptr = ft_strchr(*line,'\n')))
//	{
//		*ptr = '\0';
//
//	}
//	*ptr = '\0';
//	ptr = *line;
//	*line = ft_strdup(*line);
//	free(ptr);
//	return
//
//}

t_textures parse_line(char *line)
{
	t_textures textures;


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
		//textures = parse_line(line);
		printf("%s\n", line);
		free(line);
	}
//	len = read_map(fd, &line);
//	textures = read_line(line);
//	//printf("%s\n", line);


}