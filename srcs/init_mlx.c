/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/03/31 19:26:03 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_info(t_info *info)
{
	info->height = 480;
	info->width = 520;	
}

int	close_win_hook(t_game *game)
{
	// clean_struct_game(game, "success");
	exit (0);
	return (1);
}

int	key_press_hook(int keycode, t_game *game)
{
	if (keycode != KEY_DOWN || keycode != KEY_RIGHT
		|| keycode != KEY_LEFT || keycode != KEY_UP)
	{
		moves(game, keycode);
		draw_map_2d(game, -1, -1);
	}
	if (keycode == 65307)
		close_win_hook(game);
	return (0);
}

int	draw_map_2d(t_game *game, int i, int j)
{
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx,
					game->win, game->wall, j * 20, i * 20);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx,
					game->win, game->floor, j * 20, i * 20);
		}
		mlx_put_image_to_window(game->mlx,
			game->win, game->dot, (int)game->player->posY, (int)game->player->posX);
	}
	return (0);
}

char	**init_map2(void)
{
	char worldMap[24][26] =
	{"111111111111111111111111\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000111110000101010001\0",
	"100000100010000000000001\0",
	"100000100010000100010001\0",
	"100000100010000000000001\0",
	"100000110110000101010001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"100000000000000000000001\0",
	"111111111000000000000001\0",
	"110100001000000000000001\0",
	"110000101000000000000001\0",
	"110100001000000000000001\0",
	"110111111000000000000001\0",
	"110000000000000000000001\0",
	"111111111000000000000001\0",
	"111111111111111111111111\0"};
	return (worldMap);
}

void	init_mlx(void)
{
	t_game	game;
	int		img_width;
	int		img_height;

	init_info(&game.info);
	game.map = init_map2();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
		520, 480, "Cub3d");
	game.wall = mlx_xpm_file_to_image(game.mlx,
			"assets/texture_ea.xpm", &img_width, &img_height);
	game.floor = mlx_xpm_file_to_image(game.mlx,
			"assets/texture_no.xpm", &img_width, &img_height);
	mlx_key_hook(game.win, key_press_hook, &game);
	mlx_hook(game.win, 17, 1L << 17, close_win_hook, &game);
	mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, draw_map_2d, &game);
}