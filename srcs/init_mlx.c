/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:12:04 by acousini          #+#    #+#             */
/*   Updated: 2022/04/06 18:17:32 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_info(t_game *game)
{
	game->info.height = 480;
	game->info.width = 520;
	game->player = malloc(sizeof(raycast));
	game->player->posX = 240.00000000;
	game->player->posY = 240.00000000;
	game->player->dirX = 1.00000000;
	game->player->dirY = 0.00000001;
	game->player->planeX = 0;
	game->player->planeY = 0.66;
}

void	my_mlx_pixel_put(t_text	*data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	draw_map_2d(t_game *game, int i, int j)
{
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			// if (game->map[i][j] == '1')
			// 	mlx_put_image_to_window(game->mlx,
			// 		game->win, game->wall2d, j * 20, i * 20);
			// else if (game->map[i][j] == '0')
			// 	mlx_put_image_to_window(game->mlx,
			// 		game->win, game->floor2d, j * 20, i * 20);
		}
	}
	// mlx_put_image_to_window(game->mlx,
	// 	game->win, game->dot, (int)game->player->posX, (int)game->player->posY);
	draw_dir(game, game->player);
	return (0);
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
	map[8] = strdup("100000000000000000000001\0");
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

void	init_mlx(t_game game)
{
	int		img_width;
	int		img_height;

	init_info(&game);
	game.map = init_map2();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
		480, 480, "Cub3d");
	game.pixel.img = mlx_new_image(game.mlx, 480, 480);
	game.pixel.addr = mlx_get_data_addr(game.pixel.img, &game.pixel.bits_per_pixel, &game.pixel.line_length,
								&game.pixel.endian);
	game.wall2d = mlx_xpm_file_to_image(game.mlx,
			"assets/texture_ea.xpm", &img_width, &img_height);
	game.floor2d = mlx_xpm_file_to_image(game.mlx,
			"assets/texture_we.xpm", &img_width, &img_height);
	game.dot = mlx_xpm_file_to_image(game.mlx,
			"assets/dot.xpm", &img_width, &img_height);
	mlx_key_hook(game.win, key_press_hook, &game);
	// int i = 0;
	// while (i < 24)
	// {
	// 	printf("%s\n", game.map[i++]);
	// }
	draw_map_2d(&game, -1, -1);
	mlx_hook(game.win, 17, 1L << 17, close_win_hook, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press_hook, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release_hook, &game);
	mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, draw_map_2d, &game);
}
