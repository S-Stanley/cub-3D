/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:56:14 by acousini          #+#    #+#             */
/*   Updated: 2022/04/07 18:37:24 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		draw_cube(t_point *pos, int size, int color, text *img)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < size)
	{
		while (x < size)
		{
			if (x >= size - 1 || y >= size - 1 || x < 1 || y < 1)
				my_mlx_pixel_put(img, y + pos->x, x + pos->y, 0xd3d3d3);
			else
				my_mlx_pixel_put(img, y + pos->x, x + pos->y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

int	draw_map_2d(t_game *game, int i, int j)
{
	t_point	coord;

	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			coord.x = i * 20;
			coord.y = j * 20;
			if (game->map[i][j] == '1')
				draw_cube(&coord, 24, 0x000000, &game->pixel);
			else if (game->map[i][j] == '0')
				draw_cube(&coord, 24, 0xFFFFFF, &game->pixel);
		}
	}
	draw_dir(game, game->player);
	return (0);
}
