/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_recursive_unclose.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:03 by sserbin           #+#    #+#             */
/*   Updated: 2022/05/11 14:59:46 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_on_top(t_game game, int i, int x)
{
	while (i >= 0)
	{
		if (game.map[i][x] == '1')
			return ;
		if (game.map[i][x] == '0')
		{
			free_game(game);
			printf("Error\nMap is not closed (recursive 2)\n");
			exit(1);
		}
		i--;
	}
}

void	check_on_bottom(t_game game, int i, int x)
{
	while (game.map[i])
	{
		if (game.map[i][x] == '1')
			return ;
		if (game.map[i][x] == '0')
		{
			free_game(game);
			printf("Error\nMap is not closed (recursive 1)\n");
			exit(1);
		}
		i++;
	}
}

void	check_space(t_game game, int i, int x)
{
	if (i == 0 || i + 1 == count_len_matrice(game.map))
		return ;
	if (x == 0 || x + 1 == (int)ft_strlen(game.map[i]))
		return ;
	if (game.map[i + 1][x] == '0' || game.map[i - 1][x] == '0')
	{
		free_game(game);
		printf("Error\nMap is not closed (recursive 3)\n");
		exit(1);
	}
	if (game.map[i + 1][x] == '1' || game.map[i - 1][x] == '1')
		return ;
	if (game.map[i + 1][x] == ' ')
		check_on_top(game, i, x);
	if (game.map[i - 1][x] == ' ')
		check_on_bottom(game, i, x);
}

void	recurise_map_unclose_right(t_game game)
{
	int	i;
	int	x;

	i = 0;
	while (game.map[i])
	{
		x = ft_strlen(game.map[i]);
		while (true)
		{
			if (x == -1 || game.map[i][x] == '0')
			{
				free_game(game);
				printf("Error\nMap is not closed_cr\n");
				exit(1);
			}
			if (game.map[i][x] == '1')
				break ;
			if (game.map[i][x] == ' ')
				check_space(game, i, x);
			x--;
		}
		i++;
	}
}

void	recurise_map_unclose(t_game game)
{
	recurise_map_unclose_right(game);
	return ;
}
