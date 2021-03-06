/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceil.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 23:17:17 by stan              #+#    #+#             */
/*   Updated: 2022/05/11 17:23:23 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_final_color(t_rgb text)
{
	text.color1 = text.color1;
	text.color2 = text.color2;
	text.color3 = text.color3;
	text.final_color = ((text.color1 / 16) * 16 * 16 * 16 * 16 * 16)
		+ ((text.color1 % 16) * 16 * 16 * 16 * 16)
		+ ((text.color2 / 16) * 16 * 16 * 16)
		+ ((text.color2 % 16) * 16 * 16)
		+ ((text.color3 / 16) * 16)
		+ ((text.color3 % 16));
	return (text.final_color);
}

void	rgb_err_handler(t_game game, char **colors, char *line)
{
	(void)game;
	free(line);
	free_matrice(colors);
	printf("Error\nConfig file corrupt: RGB err\n");
	exit(1);
}

t_rgb	get_rgb_from_string(char *line, char type, t_game game)
{
	t_rgb	rgb;
	char	**colors;
	int		i;

	if (count_occurence(line, ',') != 2)
		handle_err("Error\nConfig file corrupt\n", line);
	i = 0;
	line = ft_trim(line, type);
	line = trim_line(line);
	while (line[i])
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ',')
			handle_err("Error\nConfig file corrupt\n", line);
		i++;
	}
	colors = ft_split(line, ',');
	if (count_len_matrice(colors) != 3)
		rgb_err_handler(game, colors, line);
	rgb.color1 = ft_atoi(colors[0]);
	rgb.color2 = ft_atoi(colors[1]);
	rgb.color3 = ft_atoi(colors[2]);
	rgb.final_color = get_final_color(rgb);
	free_matrice(colors);
	free(line);
	return (rgb);
}

void	check_rgb(t_game game)
{
	int		err;

	err = 0;
	if (game.ceil_color.color1 > 255 || game.ceil_color.color1 < 0)
		err = 1;
	if (game.ceil_color.color2 > 255 || game.ceil_color.color2 < 0)
		err = 1;
	if (game.ceil_color.color3 > 255 || game.ceil_color.color3 < 0)
		err = 1;
	if (game.floor_color.color1 > 255 || game.floor_color.color1 < 0)
		err = 1;
	if (game.floor_color.color2 > 255 || game.floor_color.color2 < 0)
		err = 1;
	if (game.floor_color.color3 > 255 || game.floor_color.color3 < 0)
		err = 1;
	if (err)
	{
		free_game(game);
		printf("Error\nRGB color should be between 0 and 255\n");
		exit(1);
	}
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
		if (find_index(line, "F ") >= 0 || find_index(line, "F	") >= 0)
			game.floor_color = get_rgb_from_string(line, 'F', game);
		else if (find_index(line, "C ") >= 0 || find_index(line, "C	") >= 0)
			game.ceil_color = get_rgb_from_string(line, 'C', game);
		else
			free(line);
	}
	return (game);
}
