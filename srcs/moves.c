/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:23:03 by acousini          #+#    #+#             */
/*   Updated: 2022/04/08 17:54:38 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move(t_game *game, t_point player_pos, float dir)
{
	(void)player_pos;
	float	tmp1 = (game->player->posX + game->player->dirX * dir) / 20;
	float	tmp2 = (game->player->posY + game->player->dirY * dir) / 20;
	float	tmp3 = game->player->posX / 20;
	float	tmp4 = game->player->posY / 20;
	if (game->map[(int)tmp4][(int)tmp1] == '0') 
	{
		puts(" x ");
		game->player->posX += game->player->dirX * dir;
	}
    if (game->map[(int)tmp2][(int)tmp3] == '0')
	{
		puts(" y ");
		game->player->posY += game->player->dirY * dir;
	}
	printf("  %f %f %f %f %f %f\n", game->player->posX, game->player->posY, game->player->dirX, game->player->dirY, game->player->planeX, game->player->planeY);
	printf("  %f %f \n", game->player->dirX, game->player->dirY);
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
	printf("%f %f %f %f\n", player->planeX, player->planeY, player->dirX, player->dirY);
	// printf("%f %f \n", player->dirX, player->dirY);
}

void	moves(t_game *game, int direction)
{
	t_point		player_pos;

	player_pos.x = game->player->posX;
	player_pos.y = game->player->posY;
	if (direction == KEY_UP)
		move(game, player_pos, 2.24800000);
	else if (direction == KEY_DOWN)
		move(game, player_pos, -2.24800000);
	else if (direction == KEY_LEFT)
		rotate(game, game->player, -0.1);
	else if (direction == KEY_RIGHT)
		rotate(game, game->player, 0.1);
}
