/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 22:24:14 by stan              #+#    #+#             */
/*   Updated: 2022/04/29 22:24:47 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_line_closed_top(t_game game, int i, int x)
{
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i + 1][x - 1] != '1'
			|| game.map[i + 1][x + 1] != '1')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i + 1][x] == ' ')
		{
			check_line_closed_top(game, i + 1, x);
		}
		if (game.map[i + 1][x] == '1')
			return ;
	}
}

void	check_line_closed_bottom(t_game game, int i, int x)
{
	if (game.map[i][x] == ' ')
	{
		if (game.map[i - 1][x] == '0' || game.map[i - 1][x - 1] != '1'
			|| game.map[i - 1][x + 1] != '1')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i - 1][x] == ' ')
		{
			check_line_closed_bottom(game, i - 1, x);
		}
		if (game.map[i - 1][x] == '1')
			return ;
	}
}

void	check_line_closed_right(t_game game, int i, int x)
{
	if (game.map[i][x + 1] != 0)
		return ;
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i - 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i][x - 1] == ' ')
			check_line_closed_right(game, i, x - 1);
		if (game.map[i][x - 1] == '1')
			return ;
	}
}

void	check_line_closed_left(t_game game, int i, int x)
{
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i - 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i][x + 1] == ' ')
			check_line_closed_left(game, i, x + 1);
		if (game.map[i][x + 1] == '1')
			return ;
	}
}