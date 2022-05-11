/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractor_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 01:39:30 by stan              #+#    #+#             */
/*   Updated: 2022/05/11 01:39:45 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*affect_line_map(char *line, int len)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (i < len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**refractor_map(char **map, int len)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (count_len_matrice(map) + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != len)
		{
			new_map[i] = affect_line_map(map[i], len);
			if (!new_map[i])
				new_map[i] = map[i];
		}
		else
			new_map[i] = ft_strdup(map[i]);
		i++;
	}
	new_map[i] = 0;
	free_matrice(map);
	return (new_map);
}

int	count_max_len_line(char **map)
{
	int		i;
	int		x;
	int		max;

	i = 0;
	max = -1;
	while (map[i])
	{
		x = 0;
		while (map[i][x])
			x++;
		if (x > max)
			max = x;
		i++;
	}
	return (max);
}
