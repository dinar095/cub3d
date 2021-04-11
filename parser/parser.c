/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:10:15 by desausag          #+#    #+#             */
/*   Updated: 2021/04/11 12:26:31 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game/ft_game.h"

static void	reset_textures(t_tx *tx)
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
}

static char 	**map_join(char ***map, char **line)
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

static void	 get_map(t_tx *tx, char **line)
{
	if (!(check_header(tx)))
		return;
	if ((**line == '\n' || **line == '\0' || **line == '0') && tx->map == NULL)
		return;
	tx->map = map_join(&tx->map, line);
}

static void	parse_line(char *line, t_tx *tx)
{

	if (!(ft_strncmp(line, "R ", 2)))
  		get_num_fromline(tx, &line);
	else if (!(ft_strncmp(line, "NO", 2)))
		get_char_fromline(&line, &(tx->no));
	else if (!(ft_strncmp(line, "SO", 2)))
			get_char_fromline(&line, &(tx->so));
	else if (!(ft_strncmp(line, "WE", 2)))
			get_char_fromline(&line, &(tx->we));
	else if (!(ft_strncmp(line, "EA", 2)))
			get_char_fromline(&line, &(tx->ea));
	else if (!(ft_strncmp(line, "S ", 2)))
			get_char_fromline(&line, &(tx->s));
	else if (!(ft_strncmp(line, "F ", 2)))
			get_color_fromline(&line, &(tx->f));
	else if (!(ft_strncmp(line, "C ", 2)))
			get_color_fromline(&line, &(tx->c));
	get_map(tx, &line);
}
void 	cr_pos(t_tx *tx, int dirx, int diry, int posy, int posx)
{
	tx->plr.dir.x = dirx;
	tx->plr.dir.y = diry;
	tx->plr.pos.y = posy + 0.5;
	tx->plr.pos.x = posx + 0.5;
}
void	mem_sprt(t_all *all, t_cord *art, int w)
{
	int i;

	i = -1;
	all->sp = (t_sprite *)malloc(sizeof(t_sprite) * w);
	while (++i < w)
	{
		all->sp[i].pos = art[i];
		all->sp[i].co = w;
	}
}
void	parse_plr(t_tx *tx, t_all *all)
{
	int i;
	int j;
	int w;
	t_cord art[500];

	i = -1;
	w = 0;
	while (tx->map[++i])
	{
		j = -1;
		while (tx->map[i][++j])
			if (ft_strchr("NSEW01", tx->map[i][j]))
			{
				if (ft_strchr("NSWE", tx->map[i][j]) && tx->plr.dir.y != -2)
					err("Err plr in map");
				else if (tx->map[i][j] == 'N')
					cr_pos(tx, 0, -1, i, j);
				else if (tx->map[i][j] == 'S')
					cr_pos(tx, 0, 1, i, j);
				else if (tx->map[i][j] == 'E')
					cr_pos(tx, -1, 0, i, j);
				else if (tx->map[i][j] == 'W')
					cr_pos(tx, 1, 0, i, j);
			}
			else if (tx->map[i][j] == '2')
				art[w++] = v_set(j + 0.5, i + 0.5);
			else
				err("Invalid arguments");
	}
	mem_sprt(all, art, w);
}
int open_file(char *file, t_tx *tx, t_all *all)
{
    int fd;
    char *line;
    int len;
    reset_textures(tx);
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
	parse_plr(tx, all);
	all->tx = *tx;
	all->plr = tx->plr;
	all->map = tx->map;
	all->save = 0;
    if (!(check_valid(*tx)))
        return (0);
    return (1);
}

