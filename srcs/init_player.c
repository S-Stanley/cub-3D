/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:11:26 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/16 19:11:34 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_player_dir(t_game *game, char playerDir)
{
	if (playerDir == 'N' || playerDir == 'S')
	{
		game->plr->planey = 0;
		game->plr->planex = 0.666666;
		game->plr->dirx = 0;
		game->plr->diry = -1;
		if (playerDir == 'S')
		{
			game->plr->dirx = 0;
			game->plr->diry = 1;
		}
	}
	if (playerDir == 'E' || playerDir == 'W')
	{
		game->plr->planey = 0.666666;
		game->plr->planex = 0;
		game->plr->dirx = 1;
		game->plr->diry = 0;
		if (playerDir == 'W')
		{
			game->plr->dirx = -1;
			game->plr->diry = 0;
		}
	}
}

void	init_player_pos(t_game *game)
{
	game->plr->posx = RES
		/ (ft_strlen(game->map[game->player_x]) / game->player_x);
	game->plr->posy = RES / (count_len_matrice(game->map) / game->player_y);
	game->map[game->player_y][game->player_x] = '0';
}
