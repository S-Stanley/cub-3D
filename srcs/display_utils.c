/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:03:43 by acousini          #+#    #+#             */
/*   Updated: 2022/04/15 17:08:33 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	sdist_calc(t_game *game, t_raycast *plr, int *mapx, int *mapy)
{
	int		side;

	side = plr->sdistx >= plr->sdisty;
	if (plr->sdistx < plr->sdisty)
	{
		plr->sdistx += plr->ddistx;
		*mapx += (int)(plr->stepx * 20);
	}
	else
	{
		plr->sdisty += plr->ddisty;
		*mapy += (int)(plr->stepy * 20);
	}
	plr->hit = game->map[(int)(*mapy / 20)][(int)(*mapx / 20)] == '1';
	return (side);
}

void	verline(t_game *game, int pos[3], int color)
{
	int		y;
	int		start;
	int		end;
	int		x;

	(void)color;
	start = pos[0];
	end = pos[1];
	x = pos[2];
	y = -1;
	while (++y < start)
		my_mlx_pixel_put(&game->pixel, x, y, 0xFFFF00);
	while (y < end)
		y++;
	while (y < RES)
	{
		my_mlx_pixel_put(&game->pixel, x, y, BLUE);
		y++;
	}
}

int	my_mlx_pixel_get(t_text t, float x, int y)
{
	return ((int)((int *)t.addr)[y + (int)(x * t.width)]);
}

void	my_mlx_pixel_put(t_text *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_pixel_wall(t_game *game, int pos[4], int height, float texx)
{
	int		color;
	float	texy;
	float	step;
	int		y;
	float	texpos;

	step = 1.0 * (float)TILERES / (float)height;
	texpos = ((float)pos[0] - (float)RES / 2.0 + (float)height / 2.0) * step;
	y = pos[0];
	while (y < pos[1])
	{
		texy = (int)texpos & 63;
		texpos += step;
		if (game->plr->sidehit == NO)
			color = my_mlx_pixel_get(game->no, texy, texx);
		if (game->plr->sidehit == SO)
			color = my_mlx_pixel_get(game->so, texy, texx);
		if (game->plr->sidehit == EA)
			color = my_mlx_pixel_get(game->we, texy, texx);
		if (game->plr->sidehit == WE)
			color = my_mlx_pixel_get(game->ea, texy, texx);
		my_mlx_pixel_put(&game->pixel, pos[3], y, color);
		y++;
	}
}
