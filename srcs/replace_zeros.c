/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_zeros.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:09:12 by acousini          #+#    #+#             */
/*   Updated: 2022/05/09 15:20:58 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	cross_recursive(char **map, int i, int j)
{
	if (i < )
}

void	replace_zeros(t_game *game, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
				map[i][j] = cross_recursive(map, i, j);
			
		}
	}
}
