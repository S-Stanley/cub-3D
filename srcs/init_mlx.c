/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/16 16:49:11 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_info(t_game *game)
{
	game->plr->posx = 320.00000000;
	game->plr->posy = 280.00000000;
	game->plr->dirx = -1;
	game->plr->diry = 0;
	game->plr->planex = 0;
	game->plr->planey = 0.666666;
	game->plr->hit = 0;
}

char	**init_map2(void)
{
	char **map;

	map = malloc(sizeof(char *) * 24);
	map[0] = strdup("111111111111111111111111\0");
	map[1] = strdup("100000000000000000000001\0");
	map[2] = strdup("100000000000000000000001\0");
	map[3] = strdup("100000000010000000000001\0");
	map[4] = strdup("100000000010000000000001\0");
	map[5] = strdup("100000000000000000000001\0");
	map[6] = strdup("100000000010000000000001\0");
	map[7] = strdup("100000000010000000000001\0");
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

void	load_texture(t_game *game, t_text *text, char *path)
{
	text->img = mlx_xpm_file_to_image(game->mlx, path,
			&text->width, &text->height);
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
			&text->line_length, &text->endian);
	if (text->width != text->height || text->width != 20)
	{
		write(2, "wrong texture\n", 15);
		free_game(game);
	}
}

void	init_mlx(t_game game)
{
	init_info(&game);
	game.map = init_map2();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
			game.map_res.width * 2, game.map_res.height, "Cub3d");
	game.pixel.img = mlx_new_image(game.mlx, game.map_res.width, game.map_res.height);
	game.pixel.addr = mlx_get_data_addr(game.pixel.img,
			&game.pixel.bits_per_pixel, &game.pixel.line_length,
			&game.pixel.endian);
	game.minimap.img = mlx_new_image(game.mlx, game.map_res.width, game.map_res.height);
	game.minimap.addr = mlx_get_data_addr(game.minimap.img,
			&game.minimap.bits_per_pixel, &game.minimap.line_length,
			&game.minimap.endian);
	load_texture(&game, &game.ea, "assets/textureea.xpm");
	load_texture(&game, &game.we, "assets/texturewe.xpm");
	load_texture(&game, &game.so, "assets/textureso.xpm");
	load_texture(&game, &game.no, "assets/textureno.xpm");
	draw_map_2d(&game, -1, -1);
	raycasting(&game, game.plr);
	mlx_key_hook(game.win, key_press_hook, &game);
	mlx_hook(game.win, 17, 1L << 17, close_win_hook, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press_hook, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release_hook, &game);
	mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, draw_map_2d, &game);
}
