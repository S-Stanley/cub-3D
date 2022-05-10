/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 22:24:14 by stan              #+#    #+#             */
/*   Updated: 2022/05/10 20:58:47 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_line_closed_top(t_game game, int i, int x)
{
	if (i == 0)
		return ;
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position_t %d %d\n", i, x);
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
		if (game.map[i - 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position_b %d %d\n", i, x);
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
	if (i > count_len_matrice(game.map) || i == 0)
		return ;
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i - 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position_r %d %d\n", i, x);
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
			printf("Error\nThe map is not closed at position_l %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i][x + 1] == ' ')
			check_line_closed_left(game, i, x + 1);
		if (game.map[i][x + 1] == '1')
			return ;
	}
}
