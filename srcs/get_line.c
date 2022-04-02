/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:58:09 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/02 16:58:13 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_concat(char *s1, char *s2)
{
	int		i;
	int		x;
	char	*to_return;

	if (!s2)
		return (NULL);
	i = 0;
	x = -1;
	to_return = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!to_return)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			to_return[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++x])
		to_return[i++] = s2[x];
	to_return[i] = 0;
	free(s2);
	return (to_return);
}

void	*handle_err_get_line(char *message, char *to_free)
{
	if (to_free)
		free(to_free);
	printf("%s", message);
	exit(1);
}

char	*get_line(int fd)
{
	char	*buffer;
	int		has_read;
	char	*line;

	line = NULL;
	buffer = malloc(sizeof(char) * (2));
	if (!buffer)
		return (NULL);
	while (true)
	{
		has_read = read(fd, buffer, 1);
		buffer[1] = 0;
		if (has_read == -1)
			handle_err_get_line("Error\nError while reading file\n", buffer);
		if (has_read == 0 || buffer[0] == '\n')
			break ;
		line = ft_concat(line, buffer);
		if (!line)
			handle_err_get_line("Error\nError while joining data file\n", NULL);
		buffer = malloc(sizeof(char) * (2));
		if (!buffer)
			handle_err_get_line("Error\nAllocation err reading file\n", line);
	}
	free(buffer);
	return (line);
}
