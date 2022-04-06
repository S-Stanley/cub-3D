/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:53:08 by acousini          #+#    #+#             */
/*   Updated: 2022/04/06 18:16:12 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_dir(t_game *game, raycast *player)
{
	// int		i;

	// i = 0;
	// while (i++ < )
	// {
    //   //calculate ray position and direction
    //   double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
    //   double rayDirX = dirX + planeX * cameraX;
    //   double rayDirY = dirY + planeY * cameraX;
	float	tmpRayX = player->posX;
	float	tmpRayY = player->posY;
	int		dir = 1.00000000;
	player->hit = 0;
	int i = 0;
	// t_text *lol;
	// lol = malloc(sizeof(t_text));
	// lol->img = mlx_new_image(game->mlx, 480, 520);
	// lol->addr = mlx_get_data_addr(lol->img, &lol->bits_per_pixel, &lol->line_length,
	// 							&lol->endian);
	float	tmp1;
	float	tmp2;
	float	tmp3;
	float	tmp4;
	float	tmpRayX2;
	float	tmpRayY2;
	while (i < 150)
	{
		tmpRayX2 = game->player->posX;
		tmpRayY2 = game->player->posY;
		player->cameraX = 2 * (float)i / (float)150 - 1;
		tmpRayX = player->dirX + player->planeX * player->cameraX;
		tmpRayY = player->dirY + player->planeY * player->cameraX;
		while (player->hit == 0)
		{
			tmp1 = (tmpRayX2 + tmpRayX * dir) / 20;
			tmp2 = (tmpRayY2 + tmpRayY * dir) / 20;
			tmp3 = tmpRayX2 / 20;
			tmp4 = tmpRayY2 / 20;
			if (game->map[(int)tmp4][(int)tmp1] == '0')
			{
				// puts(" x ");
				tmpRayX2 += tmpRayX * dir;
			}
			else
				player->hit = 1;
			if (game->map[(int)tmp2][(int)tmp3] == '0')
			{
				// puts(" y ");
				tmpRayY2 += tmpRayY * dir;
			}
			else
				player->hit = 1;
			if (player->hit == 0)
				my_mlx_pixel_put(&game->pixel, tmpRayY2, tmpRayX2, 0xFFFF00FF);
		}
		player->hit = 0;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, &lol, 0, 0);
	puts("HEY");
}
