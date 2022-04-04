/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:23:03 by acousini          #+#    #+#             */
/*   Updated: 2022/04/04 19:10:25 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move(t_game *game, t_point player_pos, float dir)
{
	(void)player_pos;
	if (game->map[(int)(game->player->posX + game->player->dirX * dir)][(int)game->player->posY] == 1) 
		game->player->posX += game->player->dirX * dir;
    if (game->map[(int)(game->player->posX)][(int)(game->player->posY + game->player->dirY * dir)] == 1)
		game->player->posY += game->player->dirY * dir;
}

void	rotate(t_game *game, raycast *player, float dir)
{
	float	tmpDirX;
	float	tmpPlaneX;

	(void)game;
	tmpDirX = player->dirX;
	player->dirX = player->dirX * cos(dir) - player->dirY * sin(dir);
	player->dirY = tmpDirX * sin(dir) + player->dirY * cos(dir);
	tmpPlaneX = player->planeX;
	player->planeX = player->planeX * cos(dir) - player->planeY * sin(dir);
	player->planeY = tmpPlaneX * sin(dir) + player->planeY * cos(dir);
}

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
		rotate(game, game->player, 9);
	else if (direction == KEY_RIGHT)
		rotate(game, game->player, -9);
}
