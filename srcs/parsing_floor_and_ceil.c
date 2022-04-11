/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceil.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:17:17 by stan              #+#    #+#             */
/*   Updated: 2022/04/10 09:25:39 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_rgb	get_rgb_from_string(char *line, char type)
{
	t_rgb	rgb;
	char	**colors;
	int		i;

	if (count_occurence(line, ',' > 2))
		handle_err("Error\nConfig file corrupt\n", line);
	i = 0;
	line = ft_trim(line, type);
	line = ft_trim(line, ' ');
	while (line[i])
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ',')
			handle_err("Error\nConfig file corrupt\n", line);
		i++;
	}
	colors = ft_split(line, ',');
	rgb.color1 = ft_atoi(colors[0]);
	rgb.color2 = ft_atoi(colors[1]);
	rgb.color3 = ft_atoi(colors[2]);
	free_matrice(colors);
	free(line);
	return (rgb);
}

t_game	get_floor_and_ceil(t_game game, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_err("Error\nCannot open file\n", NULL);
	while (true)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (find_index(line, "F ") >= 0)
			game.floor_color = get_rgb_from_string(line, 'F');
		else if (find_index(line, "C ") >= 0)
			game.ceil_color = get_rgb_from_string(line, 'C');
		else
			free(line);
	}
	return (game);
}
