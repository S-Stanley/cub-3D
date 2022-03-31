/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:23:03 by acousini          #+#    #+#             */
/*   Updated: 2022/03/31 19:27:18 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move(t_game *game, t_point player_pos, float dir)
{
	if (game->map[(int)(game->player->posX + game->player->dirX * dir)][(int)game->player->posY] == 1) 
		game->player->posX += game->player->dirX * dir;
    if (game->map[(int)(game->player->posX)][(int)(game->player->posY + game->player->dirY * dir)] == 1)
		game->player->posY += game->player->dirY * dir;
}

// void	rotate(t_game *game, float dir)
// {

// }

void	moves(t_game *game, int direction)
{
	t_point		player_pos;

	player_pos.x = game->player->posX;
	player_pos.y = game->player->posY;
	if (direction == KEY_UP)
		move(game, player_pos, 0.12400000);
	else if (direction == KEY_DOWN)
		move(game, player_pos, -0.12400000);
	else if (direction == KEY_LEFT)
		rotate(game, -9);
	else if (direction == KEY_RIGHT)
		rotate(game, 9);
}