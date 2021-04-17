/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:45:56 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 19:39:22 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../game/ft_game.h"

void	get_num_fromline(t_tx *tx, char **line)
{
	*line = *line + 2;
	if (tx->width != -1 || tx->height != -1)
		err("Double resolution");
	tx->width = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	while (**line != '\0' && **line == ' ')
		(*line)++;
	tx->height = ft_atoi(*line);
	while (**line >= '0' && **line <= '9')
		(*line)++;
	while (**line != '\0' && **line == ' ')
		(*line)++;
	if (**line != '\0')
		err("Invalid resolution");
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

void	h_err(t_tx *tx)
{
	if (!(tx->width > 0 && tx->height > 0))
		err("Invalid resolution");
	if (!(tx->f > -1 && tx->c > -1))
		err("Invalid color");
	if (!(tx->no && tx->so && tx->we && tx->ea && tx->s))
		err("Invalid textures");
}
