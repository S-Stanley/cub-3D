/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 19:11:26 by sserbin           #+#    #+#             */
/*   Updated: 2022/04/19 12:20:38 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_map_res(t_game *game)
{
	int		y;
	int		x;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
		}
		if (x >= game->map_res.width)
			game->map_res.width = x;
	}
	game->map_res.width *= 20;
	game->map_res.height = 20 * y;
}

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
	game->plr->posx = game->player_x * 20;
	game->plr->posy = game->player_y * 20;
	game->map[game->player_y][game->player_x] = '0';
}