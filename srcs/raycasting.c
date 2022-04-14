/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:51:20 by acousini          #+#    #+#             */
/*   Updated: 2022/04/14 18:42:32 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	verline(t_game *game, int pos[3], int color, int diff)
{
	int		y;
	int		start;
	int		end;
	int		x;

	(void)color;
	(void)diff;
	start = pos[0];
	end = pos[1];
	x = pos[2];
	y = -1;
	while (++y < start)
		my_mlx_pixel_put(&game->pixel, x, y, 0xFFFF00);
	while (y < end)
	{
		// if (x == 0)
		// 	printf(" pixel numero : %d    apres le pixel put\n", x * game->pixel.line_length + y * game->pixel.bits_per_pixel / 8);
		// if ((y >= start && y <= start + 2) || (y >= end - 2 && y <= end) || diff == 1)
		// 	my_mlx_pixel_put(&game->pixel, x, y, GREY);
		// else
		// 	my_mlx_pixel_put(&game->pixel, x, y, color);
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

// static void	walline(t_game *game, int *pos, unsigned int color[480][480], int sidehit)
// {
// 	int		y;
// 	int		start;
// 	int		end;
// 	int		x;

// 	(void)sidehit;
// 	(void)start;
// 	y = pos[0];
// 	end = pos[1];
// 	x = pos[2];
// 	// printf("my color is %u\n", color[y][x]);
// 	while (y < end)
// 	{
// 		my_mlx_pixel_put(&game->pixel, x, y, color[y][0]);
// 		y++;
// 	}
// }

static void	perpwallcalc(t_game *game, raycast *player, int side, int i, float diff)
{
	int 			lineHeight;
	int				positions[3];
	float			wallX;
	float			step;
	float			texPos;
	float			texx;
	int 			texy;
	 int				color;
	int				y;
	// static unsigned int	buffer[RES][RES];

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
		wallX = player->posY / TILERES + player->perpWallDist * player->rayDirY;
	else
		wallX = player->posX / TILERES + player->perpWallDist * player->rayDirX;
	wallX -= floorf((wallX));
	texx = (int)(wallX * (float)TILERES);
	if (side == 0 && player->rayDirX > 0)
		texx = TILERES - texx - 1;
	if (side == 1 && player->rayDirY < 0)
		texx = TILERES - texx - 1;
				// step = 1.0 * texture_choose(v, r).height / wall->line_h;
	step = 1.0 * (float)TILERES / (float)lineHeight;
				// tex_pos = ((float)pos[0].y - (float)v->c->resolution->y / 2
				// 		+ wall->line_h / 2) * step;
	texPos = ((float)positions[0] - (float)RES / 2.0 + (float)lineHeight / 2.0) * step;
	y = positions[0];
	while (y < positions[1])
	{
		// tex_y = (int)tex_pos & (texture_choose(v, r).height - 1);
		texy = (int)texPos & 63;
		// tex_pos += step;
		texPos += step;
		if (positions[2] == 0)
			printf("y = %d height %d texx %f texy %d step : %f\n",
					y - positions[0], lineHeight, texx, texy, step);
		if (player->sidehit == NO)
			color = my_mlx_pixel_get(game->no, texx, texy);
		if (player->sidehit == SO)
			color = my_mlx_pixel_get(game->so, texx, texy);
		if (player->sidehit == EA)
			color = my_mlx_pixel_get(game->we, texx, texy);
		if (player->sidehit == WE)
			color = my_mlx_pixel_get(game->ea, texx, texy);
		// if (positions[2] == 0)
		// 	printf("color is %d\n", color);
		my_mlx_pixel_put(&game->pixel, RES - i, y, color);
		// if (RES - i == 0)
		// 	printf("texy =  pixel numero : %d \n", (RES - i) * game->pixel.line_length + y * game->pixel.bits_per_pixel / 8);
		y++;
	}
	// walline(game, positions, buffer, player->sidehit);
	verline(game, positions, RED, diff);
}


static void	init_cardinal(raycast *player, int side)
{
	if (player->rayDirY < 0 && side == 1)
		player->sidehit = NO;
	else if (player->rayDirY >= 0 && side == 1)
		player->sidehit = SO;
	else if (player->rayDirX > 0 && side == 0)
		player->sidehit = EA;
	else
		player->sidehit = WE;
	
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
		init_cardinal(player, side);
		perpwallcalc(game, player, side, i, diff);
		player->hit = 0;
	}
		mlx_put_image_to_window(game->mlx, game->win, game->so.img, 440,440);
}
