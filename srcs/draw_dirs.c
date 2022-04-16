/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:53:08 by acousini          #+#    #+#             */
/*   Updated: 2022/04/16 16:46:22 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	draw_dir(t_game *game, t_raycast *plr)
{
	float	tmprayx;
	float	tmprayy;
	int		i;
	float	tmp1;
	float	tmp2;
	float	tmprayx2;
	float	tmprayy2;

	i = 0;
	while (++i <= game->map_res.width)
	{
		tmprayx2 = game->plr->posx;
		tmprayy2 = game->plr->posy;
		plr->camerax = 2 * (float)i / (float)game->map_res.width - 1;
		tmprayx = plr->dirx + plr->planex * plr->camerax;
		tmprayy = plr->diry + plr->planey * plr->camerax;
		while (plr->hit == 0)
		{
			tmp1 = (tmprayx2 + tmprayx) / TILERES;
			tmp2 = (tmprayy2 + tmprayy) / TILERES;
			if (game->map[(int)(tmprayy2 / TILERES)][(int)tmp1] == '0')
				tmprayx2 += tmprayx * 1;
			else
				plr->hit = 1;
			if (game->map[(int)tmp2][(int)(tmprayx2 / TILERES)] == '0')
				tmprayy2 += tmprayy * 1;
			else
				plr->hit = 1;
			my_mlx_pixel_put(&game->minimap, tmprayx2, tmprayy2, 0xFF0000);
			if (i == game->map_res.width / 2 | i + 1 == game->map_res.width / 2)
				my_mlx_pixel_put(&game->minimap, tmprayx2, tmprayy2, 0xFFFFFF);
		}
		plr->hit = 0;
	}
}
