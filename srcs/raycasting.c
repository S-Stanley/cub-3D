/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:51:20 by acousini          #+#    #+#             */
/*   Updated: 2022/04/12 19:07:12 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	verline(t_game *game, int pos[3], int color, int diff)
{
	int		y;
	int		start;
	int		end;
	int		x;

	start = pos[0];
	end = pos[1];
	x = pos[2];
	y = -1;
	while (++y < start)
		my_mlx_pixel_put(&game->pixel, x, y, BLACK);
	while (y < end)
	{
		if ((y >= start && y <= start + 2) || (y >= end - 2 && y <= end) || diff == 1)
			my_mlx_pixel_put(&game->pixel, x, y, GREY);
		else
			my_mlx_pixel_put(&game->pixel, x, y, color);
		y++;
	}
	while (y < RES)
	{
		my_mlx_pixel_put(&game->pixel, x, y, BLUE);
		y++;
	}
}

static void	init_sidedist_fov(raycast *player, int mapX, int mapY, int i)
{
	player->cameraX = 2 * (float)i / (float)RES - 1;
	player->rayDirX = player->dirX + player->planeX * player->cameraX;
	player->rayDirY = player->dirY + player->planeY * player->cameraX;
	player->deltaDistX = fabsf(1 / player->rayDirX);
	player->deltaDistY = fabsf(1 / player->rayDirY);
	if (player->rayDirX < 0)
	{
		player->stepX = -1;
		player->sideDistX = ((player->posX / 20) - mapX) * player->deltaDistX;
	}
	else
	{
		player->stepX = 1;
		player->sideDistX = (mapX + 1.0 - (player->posX / 20)) * player->deltaDistX;
	}
	if (player->rayDirY < 0)
	{
		player->stepY = -1;
		player->sideDistY = ((player->posY / 20) - mapY) * player->deltaDistY;
	}
	else
	{
		player->stepY = 1;
		player->sideDistY = (mapY + 1.0 - (player->posY / 20)) * player->deltaDistY;
	}
}

static void	perpwallcalc(t_game *game, raycast *player, int side, int i, float diff)
{
	int 	lineHeight;
	int		positions[3];
	float	wallX;
	int		texx;
	
	positions[2] = RES - i;
	if (side == 0)
		player->perpWallDist = (player->sideDistX - player->deltaDistX);
	else
		player->perpWallDist = (player->sideDistY - player->deltaDistY);
	lineHeight = (int)(RES / player->perpWallDist);
	positions[0] = -lineHeight / 2 + RES / 2;
	if (positions[0] < 0)
		positions[0] = 0;
	positions[1] = lineHeight / 2 + RES / 2;
	if (positions[1] >= RES)
		positions[1] = RES - 1;
	if (side == 0)
		wallX = (player->posY+ player->perpWallDist * player->rayDirY);
	else
		wallX = (player->posX + player->perpWallDist * player->rayDirX);
	wallX -= floor((wallX));
	texx = (int)(wallX * 20);
	if (side == 0 && player->rayDirX > 0) 
		texx = 20 - texx - 1;
	if (side == 1 && player->rayDirY < 0) 
		texx = 20 - texx - 1;
	if ( i == RES/2)
	{
		printf(" hitX %f ---     hitY %f ---\n", player->hitX[i], player->hitY[i]);
		printf("wallX %d ---    wallX %f ---   pour i == %d \n", texx, wallX, i);
	}
	// if (i == 0)
	// 	printf("pour 0   %f %f %f %f %f %d\n", player->perpWallDist, player->sideDistY, player->deltaDistY, player->sideDistX, player->deltaDistX, side);
	// if (i == RES / 2)
	// 	printf("pour 240   %f %f %f %d\n", player->perpWallDist, player->sideDistY, player->deltaDistY, side);
	// if (i == RES - 1)
		// printf("pour RES   %f %f %f %f %f %d\n", player->perpWallDist, player->sideDistY, player->deltaDistY, player->sideDistX, player->deltaDistX, side);
	// printf("start %d end %d perpWD %f lineH %d\n", drawStart, drawEnd, player->perpWallDist, lineHeight);
	// if (side == 0)
	// 	wallX = player->posY + player->perpWallDist * player->rayDirY;
	// else
	// 	wallX = player->posX + player->perpWallDist * player->rayDirX;
	// wallX -= floor((wallX));
	// texX = (int)(wallX * (float)texWidth);
	// if (side == 0 && rayDirX > 0)
	// 	texX = texWidth - texX - 1;
	// if (side == 1 && rayDirY < 0)
	// 	texX = texWidth - texX - 1;
	verline(game, positions, RED, diff);
}

void	raycasting(t_game *game, raycast *player)
{
	int		i;
	int		mapX;
	int		mapY;
	int 	side;
	int 	diff; 

	side = 0;
	i = -1;
	while (++i <= RES)
	{
		mapX = (int)player->posX;
		mapY = (int)player->posY;
		init_sidedist_fov(player, (int)player->posX / 20, (int)player->posY / 20, i);
		while (player->hit == 0)
		{
			side = player->sideDistX >= player->sideDistY;
			if (player->sideDistX < player->sideDistY)
			{
				player->sideDistX += player->deltaDistX;
				mapX += (int)(player->stepX * 20);
			}
			else
			{
				player->sideDistY += player->deltaDistY;
				mapY += (int)(player->stepY * 20);
			}
			player->hit = game->map[(int)(mapY / 20)][(int)(mapX / 20)] == '1';
		}
		diff = 0;
		if ((side == 0 && ((int)player->hitY[i] % 20 == 0 || (int)player->hitY[i] % 20 == 19)) ||
				(side == 1 && ((int)player->hitX[i] % 20 == 0 || (int)player->hitX[i] % 20 == 19)))
			diff = 1;
		perpwallcalc(game, player, side, i, diff);
		player->hit = 0;
	}
}