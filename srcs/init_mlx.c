/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/16 17:03:28 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_info(t_game *game)
{
	game->info.height = RES;
	game->info.width = RES;
	game->plr = malloc((sizeof (t_raycast)) + (2 * RES - 2) * sizeof (float));
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
	if (text->img == NULL)
	{
		write(2, "texture init problem\n", 22);
		free_game(game);
	}
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
			&text->line_length, &text->endian);
	if (text->addr == NULL)
	{
		write(2, "texture init problem\n", 22);
		free_game(game);
	}
}

void	load_image(t_game *game, t_text *text)
{
	text.img = mlx_new_image(game.mlx, RES, RES);
	if (text.img == NULL)
	{
		write(2, "texture init problem\n", 22);
		free_game(game);
	}
	text.addr = mlx_get_data_addr(game.text.img,
			&game.text.bits_per_pixel, &game.text.line_length,
			&game.minimap.endian);
	if (text.addr == NULL)
	{
		write(2, "texture init problem\n", 22);
		free_game(game);
	}
}

void	init_mlx(t_game game)
{
	init_info(&game);
	game.map = init_map2();
	game.mlx = mlx_init();
	if (text.mlx == NULL)
	{
		write(2, "mlx init problem\n", 19);
		free_game(game);
	}
	game.win = mlx_new_window(game.mlx,
			960, RES, "Cub3d");
	if (text.win == NULL)
	{
		write(2, "win init problem\n", 19);
		free_game(game);
	}
	load_image(&game, &game.pixel);
	load_image(&game, &game.minimap);
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
