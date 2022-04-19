/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/19 12:19:47 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_info(t_game *game)
{
	game->map_res.height = 0;
	game->map_res.width = 0;
	init_map_res(game);
	game->plr = malloc((sizeof (t_raycast)) + (2 * game->map_res.width - 2)
			* sizeof (float));
	game->plr->hit = 0;
	init_player_pos(game);
	init_player_dir(game, game->player_dir);
	printf("%d %d %f %f\n", game->map_res.height, game->map_res.width,
		game->plr->posx, game->plr->posy);
}

void	load_texture(t_game *game, t_text *text, char *path)
{
	text->img = mlx_xpm_file_to_image(game->mlx, path,
			&text->width, &text->height);
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
			&text->line_length, &text->endian);
}

void	init_mlx(t_game game)
{
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
			game.map_res.width * 2, game.map_res.height, "Cub3d");
	game.pixel.img = mlx_new_image(game.mlx, game.map_res.width,
			game.map_res.height);
	game.pixel.addr = mlx_get_data_addr(game.pixel.img,
			&game.pixel.bits_per_pixel, &game.pixel.line_length,
			&game.pixel.endian);
	game.minimap.img = mlx_new_image(game.mlx, game.map_res.width,
			game.map_res.height);
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
