/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_border.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:15:45 by sserbin           #+#    #+#             */
/*   Updated: 2022/05/11 16:17:20 by acousini         ###   ########.fr       */
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

void	check_space_open_map(t_game game, int i, int j)
{
	while (game.map[++i])
	{
		j = -1;
		while (game.map[i][++j])
		{
			if (game.map[i][j] == '0' || game.map[i][j] == 'N'
				|| game.map[i][j] == 'W' || game.map[i][j] == 'S'
				|| game.map[i][j] == 'E')
			{
				if (game.map[i + 1][j] == ' ' || game.map[i - 1][j] == ' '
					|| game.map[i][j + 1] == ' ' || game.map[i][j - 1] == ' ')
				{
					printf("0 is next to a space at position %d %d\n", i, j);
					free_game(game);
					exit(1);
				}
			}
		}
	}
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
			if (game.map[i][x] == '0' || game.map[i][x] == 'N'
				|| game.map[i][x] == 'W' || game.map[i][x] == 'S'
				|| game.map[i][x] == 'E')
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
	check_space_open_map(game, -1, -1);
}
