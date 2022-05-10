/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 01:37:45 by stan              #+#    #+#             */
/*   Updated: 2022/05/11 01:38:40 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	verif_cool_right(t_game game)
{
	int		i;
	int		x;

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
			x--;
		}
		i++;
	}
}

void	verif_cool_left(t_game game)
{
	int		i;
	int		x;

	i = 0;
	while (game.map[i])
	{
		x = 0;
		while (true)
		{
			if ((x + 1 == (int)ft_strlen(game.map[i])) || game.map[i][x] == '0')
			{
				free_game(game);
				printf("Error\nMap is not closed_cl\n");
				exit(1);
			}
			if (game.map[i][x] == '1')
				break ;
			x++;
		}
		i++;
	}
}

void	verif_cool_top(t_game game, int i, int x)
{
	if (i == count_len_matrice(game.map) + 1)
	{
		free_game(game);
		printf("Error\nMap is not closed_ct_1\n");
		exit(1);
	}
	while (x >= 0 && x < (int)ft_strlen(game.map[i]))
	{
		if (game.map[i][x] == '1')
		{
			x++;
			continue ;
		}
		if (game.map[i][x] == '0')
		{
			free_game(game);
			printf("Error\nMap is not closed_ct\n");
			exit(1);
		}
		if (game.map[i][x] == ' ')
			verif_cool_top(game, i + 1, x);
		x++;
	}
}

void	verif_cool_bottom(t_game game, int i, int x)
{
	if (i == -1)
	{
		free_game(game);
		printf("Error\nMap is not closed_cb_1 %d %d\n", i, x);
		exit(1);
	}
	while (x >= 0)
	{
		if (game.map[i][x] == '1')
		{
			x--;
			continue ;
		}
		if (game.map[i][x] == '0')
		{
			free_game(game);
			printf("Error\nMap is not closed_cb\n");
			exit(1);
		}
		if (game.map[i][x] == ' ')
			verif_cool_bottom(game, i - 1, x);
		x--;
	}
}

void	verif_cool(t_game game)
{
	verif_cool_right(game);
	verif_cool_top(game, 0, 0);
	verif_cool_left(game);
	verif_cool_bottom(game, count_len_matrice(game.map) - 1, 0);
}
