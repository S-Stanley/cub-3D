/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:53:08 by acousini          #+#    #+#             */
/*   Updated: 2022/04/24 13:48:04 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct s_tmpray {
	float	tmprayx;
	float	tmprayy;
	float	tmprayx2;
	float	tmprayy2;
	float	tmp1;
	float	tmp2;
}	t_tmpray;

t_tmpray	get_tmpray(t_game *game, t_raycast *plr)
{
	t_tmpray	tmpray;

	tmpray.tmprayx2 = game->plr->posx;
	tmpray.tmprayy2 = game->plr->posy;
	tmpray.tmprayx = plr->dirx + plr->planex * plr->camerax;
	tmpray.tmprayy = plr->diry + plr->planey * plr->camerax;
	return (tmpray);
}

t_tmpray	set_tmp_tmpray(t_tmpray tmpray)
{
	tmpray.tmp1 = (tmpray.tmprayx2 + tmpray.tmprayx) / (TILERES);
	tmpray.tmp2 = (tmpray.tmprayy2 + tmpray.tmprayy) / (TILERES);
	return (tmpray);
}

bool	check_one(t_tmpray tmpray, t_game *game)
{
	if (game->map[(int)(tmpray.tmprayy2 / (TILERES))][(int)tmpray.tmp1] == '0')
		return (true);
	return (false);
}

bool	check_two(t_tmpray tmpray, t_game *game)
{
	if (game->map[(int)tmpray.tmp2][(int)(tmpray.tmprayx2 / (TILERES))] == '0')
		return (true);
	return (false);
}

void	draw_dir(t_game *game, t_raycast *plr)
{
	int			i;
	t_tmpray	tmpray;

	i = 0;
	while (++i <= game->map_res.width)
	{
		tmpray = get_tmpray(game, plr);
		plr->camerax = 2 * (float)i / (float)game->map_res.width - 1;
		while (plr->hit == 0)
		{
			tmpray = set_tmp_tmpray(tmpray);
			if (check_one(tmpray, game))
				tmpray.tmprayx2 += tmpray.tmprayx * 1;
			else
				plr->hit = 1;
			if (check_two(tmpray, game))
				tmpray.tmprayy2 += tmpray.tmprayy * 1;
			else
				plr->hit = 1;
			my_mlx_pixel_put(&game->minimap, tmpray.tmprayx2 / 3,
				tmpray.tmprayy2 / 3, 0xd3d3d3);
		}
		plr->hit = 0;
	}
}
