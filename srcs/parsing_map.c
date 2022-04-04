/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:41:52 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/03 15:45:54 by sserbin          ###   ########.fr       */
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
			&& line[i] != 'w')
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
