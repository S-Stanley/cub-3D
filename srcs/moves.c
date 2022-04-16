/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:23:03 by acousini          #+#    #+#             */
/*   Updated: 2022/04/16 16:43:27 by acousini         ###   ########.fr       */
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

void	moves(t_game *game, int direction)
{
	if (direction == KEY_UP)
		move(game, 2.24800000);
	else if (direction == KEY_DOWN)
		move(game, -2.24800000);
	else if (direction == KEY_LEFT)
		rotate(game->plr, -0.1);
	else if (direction == KEY_RIGHT)
		rotate(game->plr, 0.1);
	mlx_put_image_to_window(game->mlx, game->win, game->pixel.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, game->map_res.width, 0);
}
