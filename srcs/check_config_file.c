/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:02:41 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/29 19:19:03 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	verif_map_parse_pos(char *filename)
{
	int		fd;
	char	*line;
	int		map_parse_started;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_err("Error\nError while opening config file\n", NULL);
	map_parse_started = 0;
	while (true)
	{
		line = get_line(fd);
		if (!line)
			break ;
		else if (is_line_map(line))
			map_parse_started = 1;
		else
			if (map_parse_started)
				handle_err("Error\nConfig file corrupt\n", line);
		free(line);
	}
	close (fd);
}

void	handle_err_matrice(char *message, char **matrice)
{
	if (matrice)
		free_matrice(matrice);
	printf("%s", message);
	exit(1);
}

void	verif_occurence_config(char *filename,
	char	*occurence, char **all_occur)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		handle_err_matrice("Error\nError while opening config file\n", all_occur);
	count = 0;
	while (true)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (find_index(line, occurence) >= 0)
			count++;
		free(line);
		if (count > 1)
			handle_err_matrice("Error\nConfig file corrupt, multiple occurence\n",
				all_occur);
	}
	close(fd);
}

char	**get_occurence_to_check(void)
{
	char	**occurence;

	occurence = malloc(sizeof(char *) * 7);
	if (!occurence)
		handle_err("Error\nAllocation err\n", NULL);
	occurence[0] = ft_strdup("NO");
	occurence[1] = ft_strdup("SO");
	occurence[2] = ft_strdup("WE");
	occurence[3] = ft_strdup("EA");
	occurence[4] = ft_strdup("F ");
	occurence[5] = ft_strdup("C ");
	occurence[6] = 0;
	return (occurence);
}

void	check_config_file(char *filename)
{
	char	**occurence;
	int		i;

	verif_map_parse_pos(filename);
	occurence = get_occurence_to_check();
	i = -1;
	while (occurence[++i])
		verif_occurence_config(filename, occurence[i], occurence);
	free_matrice(occurence);
}
