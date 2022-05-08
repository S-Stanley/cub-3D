/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_player_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 22:25:19 by stan              #+#    #+#             */
/*   Updated: 2022/04/29 22:25:26 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	verif_player_pos(t_game *game)
{
	int		i;
	int		x;

	i = 0;
	while (game->map[i])
	{
		x = 0;
		while (game->map[i][x])
		{
			if (game->map[i][x] == 'N'
				|| game->map[i][x] == 'S'
				|| game->map[i][x] == 'E'
				|| game->map[i][x] == 'W')
			{
				game->player_y = i;
				game->player_x = x;
			}
			x++;
		}
		i++;
	}
}

char	verif_player_exist(t_game game)
{
	int		i;
	int		x;

	i = 0;
	while (game.map[i])
	{
		x = 0;
		while (game.map[i][x])
		{
			if (game.map[i][x] == 'N'
				|| game.map[i][x] == 'S'
				|| game.map[i][x] == 'E'
				|| game.map[i][x] == 'W')
				return (game.map[i][x]);
			x++;
		}
		i++;
	}
	free_game(game);
	printf("Error\nDid not found player on map\n");
	exit(1);
}
