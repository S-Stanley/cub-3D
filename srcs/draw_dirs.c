/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:53:08 by acousini          #+#    #+#             */
/*   Updated: 2022/04/11 20:14:44 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_dir(t_game *game, raycast *player)
{
	float	tmpRayX = player->posX;
	float	tmpRayY = player->posY;
	int 	i;
	float	tmp1;
	float	tmp2;
	float	tmp3;
	float	tmp4;
	float	tmpRayX2;
	float	tmpRayY2;

	i = 0;
	tmpRayX = player->posY;
	tmpRayY = player->posX;
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
			tmp3 = tmpRayX2 / 20;
			tmp4 = tmpRayY2 / 20;
			if (game->map[(int)tmp4][(int)tmp1] == '0')
				tmpRayX2 += tmpRayX * 1;
			else
				player->hit = 1;
			if (game->map[(int)tmp2][(int)tmp3] == '0')
				tmpRayY2 += tmpRayY * 1;
			else
				player->hit = 1;
			if (player->hit == 0 && (i >= 1 && i <= 10))
				my_mlx_pixel_put(&game->minimap, tmpRayX2, tmpRayY2, BLUE);
			else if (player->hit == 0 && i == RES / 2)
				my_mlx_pixel_put(&game->minimap, tmpRayX2, tmpRayY2, GREY);
			else if (player->hit == 0 && (i >= RES - 10 && i <= RES))
				my_mlx_pixel_put(&game->minimap, tmpRayX2, tmpRayY2, GREY);
			else if (player->hit == 0)
				my_mlx_pixel_put(&game->minimap, tmpRayX2, tmpRayY2, 0xFF0000);
		}
		player->hit = 0;
	}
	// puts("lol");
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 480, 0);
}
