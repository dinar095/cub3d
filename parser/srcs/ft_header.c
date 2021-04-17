/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:45:56 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 13:32:24 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game/ft_game.h"

void	get_num_fromline(t_tx *tx, char **line)
{
	*line = *line + 2;
	tx->width = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	while (**line != '\0' && **line == ' ')
		(*line)++;
	tx->height = ft_atoi(*line);
}

void	get_char_fromline(char **line, char **texture)
{
	while (**line != '.' && (**line) + 1 != '/')
		(*line)++;
	*texture = ft_strdup(*line);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	get_color_fromline(char **line, int *n)
{
	int r;
	int g;
	int b;

	*line = *line + 2;
	r = ft_atoi(*line);
	while (**line >= '0' && **line <= '9' || **line == ' ')
		(*line)++;
	(*line)++;
	g = ft_atoi(*line);
	while (**line >= '0' && **line <= '9' || **line == ' ')
		(*line)++;
	(*line)++;
	b = ft_atoi(*line);
	while (**line >= '0' && **line <= '9' || **line == ' ')
		(*line)++;
	(*line)++;
	if (r > 256 || g > 256 || b > 256 || r < 0 || g < 0 || b < 0 || ft_isalpha(**line))
		err("Invalid color");
	*n = create_trgb(0, r, g, b);
}
void	ch_pth(char *txre)
{
	int fd;

	if ((fd = open(txre, O_RDONLY)) == -1)
		err("Invalid texture path");
	close(fd);

	if ((fd = open(txre, O_DIRECTORY)) != -1)
	{
		close(fd);
		err("Texture path is directory");
	}
}
int		ch_path(t_tx *tx)
{
	ch_pth(tx->no);
	ch_pth(tx->so);
	ch_pth(tx->we);
	ch_pth(tx->ea);
	return (1);

}
int		check_header(t_tx *textures)
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
	if (ch_path(textures))
		i++;
	return (i == 5 ? 1 : 0);
}

void		h_err(t_tx *tx)
{
	if (!(tx->width > 0 && tx->height > 0))
		err("Invalid resolution");
	if (!(tx->f > -1 && tx->c > -1))
		err("Invalid color");
	if (!(tx->no && tx->so && tx->we && tx->ea && tx->s))
		err("Invalid textures");
}

