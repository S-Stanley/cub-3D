/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:53:08 by acousini          #+#    #+#             */
/*   Updated: 2022/04/12 17:10:09 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_dir(t_game *game, raycast *player)
{
	float	tmpRayX;
	float	tmpRayY;
	int 	i;
	float	tmp1;
	float	tmp2;
	float	tmpRayX2;
	float	tmpRayY2;

	i = 0;
	while (++i <= RES)
	{
		tmpRayX2 = game->player->posX;
		tmpRayY2 = game->player->posY;
		player->cameraX = 2 * (float)i / (float)RES - 1;
		tmpRayX = player->dirX + player->planeX * player->cameraX;
		tmpRayY = player->dirY + player->planeY * player->cameraX;
		while (player->hit == 0)
		{
			tmp1 = (tmpRayX2 + tmpRayX * 1) / 20;
			tmp2 = (tmpRayY2 + tmpRayY * 1) / 20;
			if (game->map[(int)(tmpRayY2 / 20)][(int)tmp1] == '0')
				tmpRayX2 += tmpRayX * 1;
			else
				player->hit = 1;
			if (game->map[(int)tmp2][(int)(tmpRayX2 / 20)] == '0')
				tmpRayY2 += tmpRayY * 1;
			else
				player->hit = 1;
			my_mlx_pixel_put(&game->minimap, tmpRayX2, tmpRayY2, 0xFF0000);
		}
		player->hit = 0;
		player->hitY[i] = tmpRayY2;
		player->hitX[i] = tmpRayX2;
	}
}
