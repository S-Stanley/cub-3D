/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:23:03 by acousini          #+#    #+#             */
/*   Updated: 2023/11/22 16:50:56 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	move(t_game *game, float dir)
{
	float	tmp1;
	float	tmp2;
	float	tmp3;
	float	tmp4;

	tmp1 = (game->plr->posx + game->plr->dirx * dir) / TILERES;
	tmp2 = (game->plr->posy + game->plr->diry * dir) / TILERES;
	tmp3 = game->plr->posx / TILERES;
	tmp4 = game->plr->posy / TILERES;
	if (game->map[(int)tmp4][(int)tmp1] == '0')
		game->plr->posx += game->plr->dirx * dir;
	if (game->map[(int)tmp2][(int)tmp3] == '0')
		game->plr->posy += game->plr->diry * dir;
}

void	rotate(t_raycast *plr, float dir)
{
	float	tmpdirx;
	float	tmpplanex;

	tmpdirx = plr->dirx;
	plr->dirx = plr->dirx * cos(dir) - plr->diry * sin(dir);
	plr->diry = tmpdirx * sin(dir) + plr->diry * cos(dir);
	tmpplanex = plr->planex;
	plr->planex = plr->planex * cos(dir) - plr->planey * sin(dir);
	plr->planey = tmpplanex * sin(dir) + plr->planey * cos(dir);
}

void	moves_next(t_game *game)
{
	if (game->hooks.rotate_west == 1 && game->hooks.rotate_east == 0)
		rotate(game->plr, -0.05);
	if (game->hooks.rotate_east == 1 && game->hooks.rotate_west == 0)
		rotate(game->plr, 0.05);
	raycasting(game, game->plr);
	draw_map_2d(game, -1, 0);
}

int	moves(t_game *game)
{
	if (game->hooks.north == 1 && game->hooks.south == 0)
		move(game, 1);
	if (game->hooks.south == 1 && game->hooks.north == 0)
		move(game, -1);
	if (game->hooks.east == 1 && game->hooks.west == 0)
	{
		rotate(game->plr, 1.5705);
		move(game, 1);
		rotate(game->plr, -1.5705);
	}
	if (game->hooks.east == 0 && game->hooks.west == 1)
	{
		rotate(game->plr, 1.5705);
		move(game, -1);
		rotate(game->plr, -1.5705);
	}
	moves_next(game);
	mlx_put_image_to_window(game->mlx, game->win, game->pixel.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img,
		(game->map_res.width / 6) * 5, (game->map_res.height / 6) * 5);
	return (1);
}
