/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:35:41 by stan              #+#    #+#             */
/*   Updated: 2022/03/30 20:39:55 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_format(char *filename)
{
	int		index;

	if (!filename)
	{
		printf("Error\nFilename cannot be null\n");
		exit(1);
	}
	index = find_last_index(filename, '.');
	if (index == -1)
	{
		printf("Error\nFile do not have extention\n");
		exit(1);
	}
	if (ft_strcmp(&filename[index], ".cub") != 0)
	{
		printf("Error\nFile to parse extension should be .cub\n");
		exit(1);
	}
	if (ft_strlen(filename) < 5)
	{
		printf("Error\nFile shoud have more that just extension .cub\n");
		exit(1);
	}
}

void	check_file_access(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		printf("Error\nFile is not accessible or do not exist");
		exit(1);
	}
	close(fd);
}

void	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nWrong number of arguments\n");
		exit(1);
	}
	check_format(av[1]);
	check_file_access(av[1]);
}
