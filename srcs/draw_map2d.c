/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:56:14 by acousini          #+#    #+#             */
/*   Updated: 2022/04/20 14:44:01 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	draw_cube(t_point *pos, int size, int color, t_text *img)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y <= size)
	{
		while (x <= size)
		{
			my_mlx_pixel_put(img, x + pos->y, y + pos->x, color);
			x++;
		}
		x = 0;
		y++;
	}
}

int	draw_map_2d(t_game *game, int i, int j)
{
	t_point	coord;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			coord.x = i * TILERES / 3;
			coord.y = j * TILERES / 3;
			if (game->map[i][j] == '1')
				draw_cube(&coord, TILERES / 3, 0x000000, &game->minimap);
			else if (game->map[i][j] == '0')
				draw_cube(&coord, TILERES / 3, 0xFFFFFF, &game->minimap);
		}
	}
	draw_dir(game, game->plr);
	return (0);
}
