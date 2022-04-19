/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/19 16:44:21 by acousini         ###   ########.fr       */
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
}

void	load_texture(t_game *game, t_text *text, char *path)
{
	text->img = mlx_xpm_file_to_image(game->mlx, path,
			&text->width, &text->height);
	if (text->img == NULL)
	{
		write(2, "Texture init problem\nExit\n", 27);
		free_game_point(game);
	}
	text->addr = mlx_get_data_addr(text->img, &text->bits_per_pixel,
			&text->line_length, &text->endian);
	if (text->addr == NULL)
	{
		write(2, "Texture init problem\nExit\n", 27);
		free_game_point(game);
	}
}

void	load_image(t_game *game, t_text *text)
{
	text->img = mlx_new_image(game->mlx, game->map_res.width,
			game->map_res.height);
	if (text->img == NULL)
	{
		write(2, "Load image problem\nExit\n", 25);
		free_game_point(game);
	}
	text->addr = mlx_get_data_addr(text->img,
			&text->bits_per_pixel, &text->line_length,
			&text->endian);
	if (text->addr == NULL)
	{
		write(2, "Load image problem\nExit\n", 25);
		free_game_point(game);
	}
}

void	load_micromap(t_game *game, t_text *text)
{
	text->img = mlx_new_image(game->mlx, game->map_res.width / 3,
			game->map_res.height / 3);
	if (text->img == NULL)
	{
		write(2, "Load image problem\nExit\n", 25);
		free_game_point(game);
	}
	text->addr = mlx_get_data_addr(text->img,
			&text->bits_per_pixel, &text->line_length,
			&text->endian);
	if (text->addr == NULL)
	{
		write(2, "Load image problem\nExit\n", 25);
		free_game_point(game);
	}
}

void	init_mlx(t_game game)
{
	game.mlx = mlx_init();
	if (game.mlx == NULL)
	{
		write(2, "Mlx init problem\nExit\n", 23);
		free_game(game);
	}
	game.win = mlx_new_window(game.mlx,
			game.map_res.width, game.map_res.height, "Cub3d");
	load_image(&game, &game.pixel);
	load_micromap(&game, &game.minimap);
	load_texture(&game, &game.ea, game.texture_ea);
	load_texture(&game, &game.we, game.texture_we);
	load_texture(&game, &game.so, game.texture_so);
	load_texture(&game, &game.no, game.texture_no);
	draw_map_2d(&game, -1, -1);
	raycasting(&game, game.plr);
	mlx_put_image_to_window(game.mlx, game.win, game.pixel.img, 0, 0);
	mlx_put_image_to_window(game.mlx, game.win,
		game.minimap.img, (game.map_res.width / 3) * 2,
		(game.map_res.height / 3) * 2);
	mlx_key_hook(game.win, key_press_hook, &game);
	mlx_hook(game.win, 17, 1L << 17, close_win_hook, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press_hook, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release_hook, &game);
	mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, draw_map_2d, &game);
}
