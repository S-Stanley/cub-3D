/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:27:25 by sserbin           #+#    #+#             */
/*   Updated: 2022/05/11 17:16:05 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*trim_line(char *line)
{
	line = ft_trim(line, ' ');
	line = ft_trim(line, '	');
	return (line);
}

char	*get_texture_direction(char *direction, char *filename)
{
	char	*line;
	char	*to_return;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (true)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (find_index(line, direction) >= 0)
		{
			line = trim_line(line);
			to_return = ft_strdup(&line[2]);
			free(line);
			return (to_return);
		}
		line = trim_line(line);
		free(line);
	}
	close(fd);
	return (NULL);
}

void	verif_path_texture(t_game game)
{
	int		fd;
	int		err;

	err = 0;
	fd = open(game.texture_no, O_RDONLY);
	if (fd == -1)
		err = 1;
	fd = open(game.texture_so, O_RDONLY);
	if (fd == -1)
		err = 1;
	fd = open(game.texture_we, O_RDONLY);
	if (fd == -1)
		err = 1;
	fd = open(game.texture_ea, O_RDONLY);
	if (fd == -1)
		err = 1;
	if (err)
	{
		printf("Error\nInaccessible file texture\n");
		free_game(game);
		exit(1);
	}
}

t_game	get_texture(t_game game, char *filename)
{
	game.texture_ea = get_texture_direction("EA", filename);
	game.texture_no = get_texture_direction("NO", filename);
	game.texture_so = get_texture_direction("SO", filename);
	game.texture_we = get_texture_direction("WE", filename);
	if (!game.texture_no || !game.texture_so
		|| !game.texture_we || !game.texture_ea)
	{
		free_game(game);
		printf("Error\nDid not found one of the textures\n");
		exit(1);
	}
	verif_path_texture(game);
	return (game);
}
