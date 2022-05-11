/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:46:16 by sserbin           #+#    #+#             */
/*   Updated: 2022/05/11 17:32:30 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**get_arr_unexpected_statement(void)
{
	char	**to_find;

	to_find = NULL;
	to_find = push_arr(to_find, ft_strdup("NO "));
	to_find = push_arr(to_find, ft_strdup("NO	"));
	to_find = push_arr(to_find, ft_strdup("SO "));
	to_find = push_arr(to_find, ft_strdup("SO	"));
	to_find = push_arr(to_find, ft_strdup("WE "));
	to_find = push_arr(to_find, ft_strdup("WE	"));
	to_find = push_arr(to_find, ft_strdup("EA "));
	to_find = push_arr(to_find, ft_strdup("EA	"));
	to_find = push_arr(to_find, ft_strdup("C "));
	to_find = push_arr(to_find, ft_strdup("C	"));
	to_find = push_arr(to_find, ft_strdup("F "));
	to_find = push_arr(to_find, ft_strdup("F	"));
	return (to_find);
}

bool	check_unexpected_statement(char *line)
{
	char	**to_find;
	int		i;

	i = 0;
	to_find = get_arr_unexpected_statement();
	while (to_find[i])
	{
		if (find_index(line, to_find[i]) >= 0)
		{
			free_matrice(to_find);
			return (true);
		}
		i++;
	}
	if (!is_line_map(line))
	{
		free_matrice(to_find);
		return (false);
	}
	free_matrice(to_find);
	return (true);
}

bool	check_garbage(char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (false);
	while (true)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (!check_unexpected_statement(line))
		{
			close(fd);
			free(line);
			printf("Error\nConfig file unexpected statement\n");
			exit(1);
		}
		free(line);
	}
	close(fd);
	return (true);
}
