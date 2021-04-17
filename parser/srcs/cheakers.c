/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheakers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 21:27:21 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 21:27:21 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game/ft_game.h"

int				at_karusel(char **line, int flag)
{
	int c;

	c = 0;
	while (**line == ' ')
		(*line)++;
	while (**line >= '0' && **line <= '9')
		(*line)++;
	while (**line == ' ')
		(*line)++;
	if (**line == ',' && flag == 0)
	{
		(*line)++;
		c++;
	}
	return (c);
}

void			get_color_fromline(char **line, int *n)
{
	int r;
	int g;
	int b;
	int c;

	c = 0;
	*line = *line + 2;
	r = ft_atoi(*line);
	c += at_karusel(line, 0);
	g = ft_atoi(*line);
	c += at_karusel(line, 0);
	b = ft_atoi(*line);
	at_karusel(line, 1);
	if (**line != '\0' || b < 0 || r > 256
		|| g > 256 || b > 256 || r < 0 || g < 0 || c != 2)
		err("Invalid color");
	*n = create_trgb(0, r, g, b);
}

static void		ch_pth(char *txre)
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

static int		ch_path(t_tx *tx)
{
	ch_pth(tx->no);
	ch_pth(tx->so);
	ch_pth(tx->we);
	ch_pth(tx->ea);
	return (1);
}

int				check_header(t_tx *textures)
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
