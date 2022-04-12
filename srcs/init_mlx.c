/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/12 17:06:56 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_info(t_game *game)
{
	game->info.height = RES;
	game->info.width = RES;
	game->player = malloc((sizeof (raycast)) + (2 * RES - 2) * sizeof (float));
	game->player->posX = 320.00000000;
	game->player->posY = 280.00000000;
	game->player->dirX = -1;
	game->player->dirY = 0;
	game->player->planeX = 0;
	game->player->planeY = 0.666666;
	game->player->hit = 0;
}

void	my_mlx_pixel_put(text *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

char	**init_map2(void)
{
	char **map;

	map = malloc(sizeof(char *) * 24);
	map[0] = strdup("111111111111111111111111\0");
	map[1] = strdup("100000000000000000000001\0");
	map[2] = strdup("100000000000000000000001\0");
	map[3] = strdup("100000000000000000000001\0");
	map[4] = strdup("100000000000000000000001\0");
	map[5] = strdup("100000000000000000000001\0");
	map[6] = strdup("100000000000000000000001\0");
	map[7] = strdup("100000000000000000000001\0");
	map[8] = strdup("100001111110000000000001\0");
	map[9] = strdup("100000000000000000000001\0");
	map[10] = strdup("100000000000000000000001\0");
	map[11] = strdup("100000000000000000000001\0");
	map[12] = strdup("100000000000000000000001\0");
	map[13] = strdup("100000000000000000000001\0");
	map[14] = strdup("100000000000000000000001\0");
	map[15] = strdup("100000000000000000000001\0");
	map[16] = strdup("100000000000000000000001\0");
	map[17] = strdup("100000000000000000000001\0");
	map[18] = strdup("100000000000000000000001\0");
	map[19] = strdup("100000000000000000000001\0");
	map[20] = strdup("100000000000000000000001\0");
	map[21] = strdup("100000000000000000000001\0");
	map[22] = strdup("100000000000000000000001\0");
	map[23] = strdup("111111111111111111111111\0");
	return (map);
}

void			load_texture(t_game *game, text *text, char *path)
{
	text->img = mlx_xpm_file_to_image(game->mlx, path, &text->width, &text->height);
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
						&text->line_length, &text->endian);
}

void	init_mlx(t_game game)
{
	init_info(&game);
	game.map = init_map2();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
		960, RES, "Cub3d");
	game.pixel.img = mlx_new_image(game.mlx, RES, RES);
	game.pixel.addr = mlx_get_data_addr(game.pixel.img, &game.pixel.bits_per_pixel, &game.pixel.line_length,
								&game.pixel.endian);
	game.minimap.img = mlx_new_image(game.mlx, RES, RES);
	game.minimap.addr = mlx_get_data_addr(game.minimap.img, &game.minimap.bits_per_pixel, &game.minimap.line_length,
								&game.minimap.endian);
	load_texture(&game, &game.wall2d, "assets/texture_ea.xpm");
	load_texture(&game, &game.floor2d, "assets/texture_we.xpm");
	load_texture(&game, &game.dot, "assets/dot.xpm");
	mlx_key_hook(game.win, key_press_hook, &game);
	draw_map_2d(&game, -1, -1);
	mlx_hook(game.win, 17, 1L << 17, close_win_hook, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press_hook, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release_hook, &game);
	mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, draw_map_2d, &game);
}
