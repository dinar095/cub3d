/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/04/17 18:32:09 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game/ft_game.h"

static void		reset_textures(t_tx *tx, t_all *all)
{
	tx->width = -1;
	tx->height = -1;
	tx->no = NULL;
	tx->so = NULL;
	tx->we = NULL;
	tx->ea = NULL;
	tx->s = NULL;
	tx->f = -1;
	tx->c = -1;
	tx->map = NULL;
	tx->plr.dir.y = -2;
	all->spr_co = 0;
}

static char		**map_join(char ***map, char **line)
{
	char	**ret;
	size_t	i;
	size_t	n;

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
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	while (++n < i)
		*(ret + n) = *(*map + n);
	ret[n++] = ft_strdup(*line);
	ret[n] = NULL;
	free(*map);
	return (ret);
}

static void		get_map(t_tx *tx, char **line)
{
	h_err(tx);
	if ((**line == '\n' || **line == '\0' || **line == '0') && tx->map == NULL)
		return ;
	tx->map = map_join(&tx->map, line);
}

int				ch_double_tx(char *tx)
{
	if (tx == NULL)
		return (1);
	else
		err("Double texture path");
}

int				ch_double_col(int col)
{
	if (col == -1)
		return (1);
	else
		err("Double color");
}

static void		parse_line(char *line, t_tx *tx)
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

void			cr_pos(t_tx *tx, t_int dir, t_int pos)
{
	tx->plr.dir.x = dir.i;
	tx->plr.dir.y = dir.j;
	tx->plr.pos.y = pos.i + 0.5;
	tx->plr.pos.x = pos.j + 0.5;
	tx->map[pos.i][pos.j] = '0';
}

void			mem_sprt(t_all *all, t_cord *art)
{
	int i;

	i = -1;
	all->sp = (t_sprite *)malloc(sizeof(t_sprite) * all->spr_co);
	while (++i < all->spr_co)
		all->sp[i].pos = art[i];
}

void			cr_plr(t_tx *tx, t_int i_j)
{
	if (ft_strchr("NSWE", tx->map[i_j.i][i_j.j]) && tx->plr.dir.y != -2)
		err("Invalid player");
	else if (tx->map[i_j.i][i_j.j] == 'N')
		cr_pos(tx, v_int(0, -1), v_int(i_j.i, i_j.j));
	else if (tx->map[i_j.i][i_j.j] == 'S')
		cr_pos(tx, v_int(0, 1), v_int(i_j.i, i_j.j));
	else if (tx->map[i_j.i][i_j.j] == 'E')
		cr_pos(tx, v_int(-1, 0), v_int(i_j.i, i_j.j));
	else if (tx->map[i_j.i][i_j.j] == 'W')
		cr_pos(tx, v_int(1, 0), v_int(i_j.i, i_j.j));
}

void			parse_plr(t_tx *tx, t_all *all)
{
	t_int	i_j;
	int		w;
	t_cord	art[10000];

	i_j.i = -1;
	w = 0;
	while (tx->map[++i_j.i])
	{
		i_j.j = -1;
		while (tx->map[i_j.i][++i_j.j])
			if (ft_strchr("NSEW01 ", tx->map[i_j.i][i_j.j]))
				cr_plr(tx, i_j);
			else if (tx->map[i_j.i][i_j.j] == '2')
				art[w++] = v_set(i_j.j + 0.5, i_j.i + 0.5);
			else
				err("Invalid arguments in map");
	}
	if (tx->plr.dir.y == -2)
		err("No player in map");
	all->spr_co = w;
	if (all->spr_co > 0)
		mem_sprt(all, art);
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
