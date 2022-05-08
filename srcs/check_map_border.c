/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:15:45 by sserbin           #+#    #+#             */
/*   Updated: 2022/05/08 15:34:33 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	len_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

bool	line_before_len_is_lower(t_game game, int i)
{
	int	line;
	int	line_before;

	if (i >= len_map(game.map))
		return (false);
	line = 0;
	while (game.map[i][line])
		line++;
	line_before = 0;
	i++;
	while (game.map[i][line_before])
		line_before++;
	return (line_before < line);
}

void	check_err_open_map(t_game game)
{
	int		i;
	int		x;

	i = -1;
	while (game.map[++i])
	{
		x = -1;
		while (game.map[i][++x])
		{
			if (game.map[i][x] == '0')
			{
				if (line_before_len_is_lower(game, i)
					&& game.map[i][x + 1] == '1' && !game.map[i][x + 2]
				)
				{
					printf("Map is not closed at position %d %d\n", i, x);
					free_game(game);
					exit(1);
				}
			}
		}
	}
}
