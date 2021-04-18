/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/04/18 08:50:17 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game/ft_game.h"

int				check_ext(const char *f_name)
{
	int	c;

	c = ft_strlen(f_name);
	if (c > 6 && !ft_strncmp(f_name + (c - 4), ".cub", 4))
		return (1);
	return (0);
}

static int		ch_double_col(int col)
{
	if (col == -1)
		return (1);
	else
		err("Double color");
	return (0);
}

void			mem_sprt(t_all *all, t_cord *art)
{
	int i;

	i = -1;
	all->sp = NULL;
	if (!(all->sp = (t_sprite *)malloc(sizeof(t_sprite) * all->spr_co)))
		err("Can't allocated for sprites");
	while (++i < all->spr_co)
		all->sp[i].pos = art[i];
}

void			parse_line(char *line, t_tx *tx)
{
	if (!(ft_strncmp(line, "R ", 2)))
		get_num_fromline(tx, &line);
	else if (!(ft_strncmp(line, "NO ", 3)) && ch_double_tx(tx->no))
		get_char_fromline(&line, &(tx->no));
	else if (!(ft_strncmp(line, "SO ", 3)) && ch_double_tx(tx->so))
		get_char_fromline(&line, &(tx->so));
	else if (!(ft_strncmp(line, "WE ", 3)) && ch_double_tx(tx->we))
		get_char_fromline(&line, &(tx->we));
	else if (!(ft_strncmp(line, "EA ", 3)) && ch_double_tx(tx->ea))
		get_char_fromline(&line, &(tx->ea));
	else if (!(ft_strncmp(line, "S ", 2)) && ch_double_tx(tx->s))
		get_char_fromline(&line, &(tx->s));
	else if (!(ft_strncmp(line, "F ", 2)) && ch_double_col(tx->f))
		get_color_fromline(&line, &(tx->f));
	else if (!(ft_strncmp(line, "C ", 2)) && ch_double_col(tx->c))
		get_color_fromline(&line, &(tx->c));
	else if (check_header(tx))
		get_map(tx, &line);
}

int				open_file(char *file, t_tx *tx, t_all *all)
{
	int		fd;
	char	*line;
	int		len;

	reset_textures(tx, all);
	len = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		err("Error file");
	while (len && fd != -1)
	{
		len = get_next_line(fd, &line);
		parse_line(line, tx);
		free(line);
	}
	close(fd);
	h_err(tx);
	if (!(check_valid(*tx)))
		err("Invalid map");
	parse_plr(tx, all);
	all->tx = *tx;
	all->plr = tx->plr;
	all->map = tx->map;
	return (1);
}
