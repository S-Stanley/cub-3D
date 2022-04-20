/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:23:03 by acousini          #+#    #+#             */
/*   Updated: 2022/04/20 15:06:48 by acousini         ###   ########.fr       */
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

int	moves(t_game *game)
{
	if (game->hooks.north == 1 && game->hooks.south == 0)
		move(game, 2.24800000);
	if (game->hooks.south == 1 && game->hooks.north == 1)
		move(game, -2.24800000);
	if (game->hooks.rotate_west == 1 && game->hooks.rotate_east == 0)
		rotate(game->plr, -0.1);
	if (game->hooks.rotate_east == 1 && game->hooks.rotate_west == 0)
		rotate(game->plr, 0.1);
	raycasting(game, game->plr);
	draw_map_2d(game, -1, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->pixel.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win,
		game->minimap.img, (game->map_res.width / 3) * 2,
		(game->map_res.height / 3) * 2);
	return (1);
}
