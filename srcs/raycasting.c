/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:51:20 by acousini          #+#    #+#             */
/*   Updated: 2022/04/15 17:08:53 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_sidedist_fov(t_raycast *plr, int mapX, int mapY, int i)
{
	plr->camerax = 2 * (float)i / (float)RES - 1;
	plr->raydirx = plr->dirx + plr->planex * plr->camerax;
	plr->raydiry = plr->diry + plr->planey * plr->camerax;
	plr->ddistx = fabsf(1 / plr->raydirx);
	plr->ddisty = fabsf(1 / plr->raydiry);
	if (plr->raydirx < 0)
	{
		plr->stepx = -1;
		plr->sdistx = ((plr->posx / 20) - mapX) * plr->ddistx;
	}
	else
	{
		plr->stepx = 1;
		plr->sdistx = (mapX + 1.0 - (plr->posx / 20)) * plr->ddistx;
	}
	if (plr->raydiry < 0)
	{
		plr->stepy = -1;
		plr->sdisty = ((plr->posy / 20) - mapY) * plr->ddisty;
	}
	else
	{
		plr->stepy = 1;
		plr->sdisty = (mapY + 1.0 - (plr->posy / 20)) * plr->ddisty;
	}
}

int	texx_init(t_game *game, int pos[3], int height)
{
	float	wallx;
	float	texx;

	(void)pos;
	(void)height;
	if (game->plr->sidehit == 2 || game->plr->sidehit == 3)
		wallx = game->plr->posy / TILERES
			+ game->plr->perp * game->plr->raydiry;
	else
		wallx = game->plr->posx / TILERES
			+ game->plr->perp * game->plr->raydirx;
	wallx -= floorf((wallx));
	texx = (int)(wallx * (float)TILERES);
	if (game->plr->sidehit == EA && game->plr->raydirx > 0)
		texx = TILERES - texx - 1;
	if (game->plr->sidehit == NO && game->plr->raydiry < 0)
		texx = TILERES - texx - 1;
	return (texx);
}

static void	perpwallcalc(t_game *game, t_raycast *plr, int side, int i)
{
	int				height;
	int				pos[4];
	float			texx;

	pos[2] = RES - i;
	if (side == 0)
		plr->perp = (plr->sdistx - plr->ddistx);
	else
		plr->perp = (plr->sdisty - plr->ddisty);
	height = (int)(RES / plr->perp);
	pos[0] = -height / 2 + RES / 2;
	if (pos[0] < 0)
		pos[0] = 0;
	pos[1] = height / 2 + RES / 2;
	if (pos[1] >= RES)
		pos[1] = RES - 1;
	texx = texx_init(game, pos, height);
	pos[3] = RES - i;
	draw_pixel_wall(game, pos, height, texx);
	verline(game, pos, RED);
}

static void	init_cardinal(t_raycast *plr, int side)
{
	if (plr->raydiry < 0 && side == 1)
		plr->sidehit = NO;
	else if (plr->raydiry >= 0 && side == 1)
		plr->sidehit = SO;
	else if (plr->raydirx > 0 && side == 0)
		plr->sidehit = EA;
	else
		plr->sidehit = WE;
}

void	raycasting(t_game *game, t_raycast *plr)
{
	int		i;
	int		mapx;
	int		mapy;
	int		side;

	side = 0;
	i = -1;
	while (++i <= RES)
	{
		mapx = (int)plr->posx;
		mapy = (int)plr->posy;
		init_sidedist_fov(plr, (int)plr->posx / 20, (int)plr->posy / 20, i);
		while (plr->hit == 0)
		{
			side = sdist_calc(game, plr, &mapx, &mapy);
		}
		init_cardinal(plr, side);
		perpwallcalc(game, plr, side, i);
		plr->hit = 0;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->so.img, 420, 440);
	mlx_put_image_to_window(game->mlx, game->win, game->no.img, 400, 440);
	mlx_put_image_to_window(game->mlx, game->win, game->we.img, 380, 440);
	mlx_put_image_to_window(game->mlx, game->win, game->ea.img, 360, 440);
}
