/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixtures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:51:48 by stan              #+#    #+#             */
/*   Updated: 2022/04/19 15:06:24 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	verif_player_pos(t_game *game)
{
	int		i;
	int		x;

	i = 0;
	while (game->map[i])
	{
		x = 0;
		while (game->map[i][x])
		{
			if (game->map[i][x] == 'N'
				|| game->map[i][x] == 'S'
				|| game->map[i][x] == 'E'
				|| game->map[i][x] == 'W')
			{
				game->player_y = i;
				game->player_x = x;
			}
			x++;
		}
		i++;
	}
}

char	verif_player_exist(t_game game)
{
	int		i;
	int		x;

	i = 0;
	while (game.map[i])
	{
		x = 0;
		while (game.map[i][x])
		{
			if (game.map[i][x] == 'N'
				|| game.map[i][x] == 'S'
				|| game.map[i][x] == 'E'
				|| game.map[i][x] == 'W')
				return (game.map[i][x]);
			x++;
		}
		i++;
	}
	free_game(game);
	printf("Error\nDid not found player on map\n");
	exit(1);
}

void	verif_map_config(t_game game)
{
	int		i;
	int		x;

	i = 0;
	while (game.map[i])
	{
		x = 0;
		while (game.map[i][x])
		{
			if (game.map[i][x] != 'N'
				&& game.map[i][x] != 'S'
				&& game.map[i][x] != 'E'
				&& game.map[i][x] != 'W'
				&& game.map[i][x] != '1'
				&& game.map[i][x] != '0'
				&& game.map[i][x] != ' ')
			{
				free_game(game);
				printf("Error\nUnexpected char in map\n");
				exit(1);
			}
			x++;
		}
		i++;
	}
}

t_game	init_game(char *filename)
{
	t_game		game;

	game.player_dir = PLAYER_DIR_NO;
	game = get_floor_and_ceil(game, filename);
	game.map = parse_map(filename);
	if (!game.map)
	{
		printf("Error\nMap parsing failed\n");
		exit(1);
	}
	game = get_texture(game, filename);
	verif_map_config(game);
	verif_map_closed(game);
	verif_player_exist(game);
	game.player_dir = verif_player_exist(game);
	verif_player_pos(&game);
	return (game);
}

void	free_game(t_game game)
{
	if (game.texture_no)
		free(game.texture_no);
	if (game.texture_so)
		free(game.texture_so);
	if (game.texture_we)
		free(game.texture_we);
	if (game.texture_ea)
		free(game.texture_ea);
	free_matrice(game.map);
}

void	free_game_point(t_game *game)
{
	if (game->texture_no)
		free(game->texture_no);
	if (game->texture_so)
		free(game->texture_so);
	if (game->texture_we)
		free(game->texture_we);
	if (game->texture_ea)
		free(game->texture_ea);
	free_matrice(game->map);
	if (game->plr)
		free(game->plr);
}
