/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:51:20 by acousini          #+#    #+#             */
/*   Updated: 2022/04/11 20:16:12 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	verline(t_game *game, int x, int start, int end, int color, int diff)
{
	int		y;

	y = -1;
	while (++y < start)
	{
		// printf("y = %d x = %d start %d end %d\n", y, x, start, end);
		my_mlx_pixel_put(&game->pixel, x, y, BLACK);
	}
	while (y++ < end)
	{
		if (x == RES / 2)
			my_mlx_pixel_put(&game->pixel, x, y, GREEN);
		else if ((y >= start && y <= start + 1) || (y >= end - 1 && y <= end) || diff == 1)
			my_mlx_pixel_put(&game->pixel, x, y, GREY);
		else
			my_mlx_pixel_put(&game->pixel, x, y, color);
	}
	while (++y < RES)
		my_mlx_pixel_put(&game->pixel, x, y, BLUE);
}

void	init_sidedist(raycast *player, int mapX, int mapY)
{
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

void	init_touchdist(raycast *player, int mapX, int mapY)
{
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

void	perpwallcalc(t_game *game, raycast *player, int side, int i, float diff)
{
	int 	lineHeight;
	int 	drawEnd;
	int 	drawStart;
	// float	wallX;
	// int 	texX;
	
	if (side == 0)
		player->perpWallDist = (player->sideDistX - player->deltaDistX);
	else
		player->perpWallDist = (player->sideDistY - player->deltaDistY);
	// printf("sideX : %f  sideY : %f  deltaX : %f  deltaY : %f\n", player->sideDistX, player->sideDistY, player->deltaDistX, player->deltaDistY);
	lineHeight = (int)(RES / player->perpWallDist);
	drawStart = -lineHeight / 2 + RES / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + RES / 2;
	if (drawEnd >= RES)
		drawEnd = RES - 1;
	// if (i == 0)
	// 	printf("pour 0   %f %f %f %f %f %d\n", player->perpWallDist, player->sideDistY, player->deltaDistY, player->sideDistX, player->deltaDistX, side);
	if (i == RES / 2)
		printf("pour 240   %f %f %f %d\n", player->perpWallDist, player->sideDistY, player->deltaDistY, side);
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
	verline(game, RES - i, drawStart, drawEnd, RED, diff);
}

void	raycasting(t_game *game, raycast *player)
{
	int		i;
	int	mapX;
	int	mapY;
	int 	side;

	side = 0;
	i = -1;
	// printf("sideX : %f sideY : %f deltX : %f deltY : %f\n", game->player->sideDistX, game->player->sideDistY,
	// 	game->player->deltaDistX, game->player->deltaDistY);
	while (++i < RES)
	{
		mapX = (int)player->posX;
		mapY = (int)player->posY;
		float	fMapX = player->posX;
		float	fMapY = player->posY;
		player->cameraX = 2 * (float)i / (float)RES - 1;
		player->rayDirX = player->dirX + player->planeX * player->cameraX;
		player->rayDirY = player->dirY + player->planeY * player->cameraX;
		init_sidedist(player, (int)player->posX / 20, (int)player->posY / 20);
		if (i == RES / 2)
			printf("sideX : %f\tsideY : %f\tdeltaX : %f\tdeltaY : %f\n", player->sideDistX, player->sideDistY, player->deltaDistX, player->deltaDistY);
		while (player->hit == 0)
		{
			if (player->sideDistX < player->sideDistY)
			{
				player->sideDistX += player->deltaDistX;
				mapX += (int)(player->stepX * 20);
				fMapX += (player->stepX * 20);
				side = 0;
			}
			else
			{
				player->sideDistY += player->deltaDistY;
				mapY += (int)(player->stepY * 20);
				fMapY += (player->stepY * 20);
				side = 1;
			}
			if (game->map[(int)(mapY / 20)][(int)(mapX / 20)] == '1')
				player->hit = 1;
		}
		int diff = 0;
		if (((int)fMapX % 20 == 0 && side == 1) || ((int)fMapY % 20 == 0 && side == 0))
			diff = 1;
		if (i == RES / 2)
			printf("mapX %f mapY %f\t\t", fMapX, fMapY);
		perpwallcalc(game, player, side, i, diff);
		player->hit = 0;
	}
	// printf("avant window");
	mlx_put_image_to_window(game->mlx, game->win, game->pixel.img, 0, 0);
	// printf("\n apres");
}