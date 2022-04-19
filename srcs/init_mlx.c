/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/16 17:03:28 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_info(t_game *game)
{
	game->map_res.height = RES;
	game->map_res.width = RES;
	game->plr = malloc((sizeof (t_raycast)) + (2 * RES - 2) * sizeof (float));
	game->plr->hit = 0;
	init_player_pos(game);
	init_player_dir(game, game->player_dir);
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