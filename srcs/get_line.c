/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:58:09 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/29 20:11:49 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*handle_err(char *message, char *to_free)
{
	if (to_free)
		free(to_free);
	printf("%s", message);
	exit(1);
}

char	*get_malloc_buffer(int size, char *line)
{
	char	*buffer;

	buffer = malloc(size);
	if (!buffer)
		handle_err("Error\nAllocation err reading file\n", line);
	return (buffer);
}

bool	check_err_map(int len_map, char *buffer, char **map, int fd)
{
	char	buff[2];
	int		nb;

	if (len_map > 0)
	{
		while (true)
		{
			nb = read(fd, buff, 1);
			buff[1] = 0;
			if (nb == 0)
			{
				free(buffer);
				return (true);
			}
			if (buff[0] != ' ' && buff[0] != '\n')
				break ;
		}
		printf("Error\nMap cannot have empty line\n");
		free(buffer);
		free_matrice(map);
		exit(1);
	}
	free(buffer);
	return (true);
}

char	*get_line_for_map(int fd, int len_map, char **map)
{
	char	*buffer;
	int		has_read;
	char	*line;

	line = NULL;
	while (true)
	{
		buffer = get_malloc_buffer(sizeof(char) * (2), line);
		has_read = read(fd, buffer, 1);
		buffer[1] = 0;
		if (has_read == -1)
			handle_err("Error\nError while reading file\n", buffer);
		if (has_read == 0 || (buffer[0] == '\n' && line))
			break ;
		if (buffer[0] == '\n' && !line)
			if (check_err_map(len_map, buffer, map, fd))
				continue ;
		line = ft_concat(line, buffer);
		if (!line)
			handle_err("Error\nError while joining data file\n", NULL);
	}
	free(buffer);
	return (line);
}

char	*get_line(int fd)
{
	char	*buffer;
	int		has_read;
	char	*line;

	line = NULL;
	while (true)
	{
		buffer = get_malloc_buffer(sizeof(char) * (2), line);
		has_read = read(fd, buffer, 1);
		buffer[1] = 0;
		if (has_read == -1)
			handle_err("Error\nError while reading file\n", buffer);
		if (has_read == 0 || (buffer[0] == '\n' && line))
			break ;
		if (buffer[0] == '\n' && !line)
		{
			free(buffer);
			continue ;
		}
		line = ft_concat(line, buffer);
		if (!line)
			handle_err("Error\nError while joining data file\n", NULL);
	}
	free(buffer);
	return (line);
}
