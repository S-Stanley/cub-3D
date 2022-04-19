/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:41:52 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/16 19:24:22 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	is_line_map(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (false);
	while (line[i])
	{
		if (line[i] != '0'
			&& line[i] != '1'
			&& line[i] != ' '
			&& line[i] != 'N'
			&& line[i] != 'S'
			&& line[i] != 'E'
			&& line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

char	**parse_map(char *filename)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = NULL;
	while (true)
	{
		line = get_line(fd);
		if (!line)
			break ;
		else if (is_line_map(line))
			map = push_arr(map, line);
		else
			free(line);
	}
	close(fd);
	return (map);
}

bool	check_map_line(char *line, bool top_or_bottom)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (top_or_bottom)
		{
			if (line[i] != '1' && line[i] != ' ')
				return (false);
		}
		else
		{
			if (i == 0 || !line[i + 1])
				if (line[i] != '1' && line[i] != ' ')
					return (false);
		}
		i++;
	}
	return (true);
}

void	verif_map_closed(t_game game)
{
	int		i;
	bool	top_or_bottom;

	i = 0;
	top_or_bottom = true;
	while (game.map[i])
	{
		if (i == 0 || !game.map[i + 1])
			top_or_bottom = true;
		else
			top_or_bottom = false;
		if (!check_map_line(game.map[i], top_or_bottom))
		{
			free_game(game);
			printf("Error\nMap is not closed\n");
			exit(1);
		}
		i++;
	}
}
