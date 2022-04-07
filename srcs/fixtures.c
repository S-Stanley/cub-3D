/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixtures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:51:48 by stan              #+#    #+#             */
/*   Updated: 2022/04/05 20:49:45 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	**init_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 7);
	if (!map)
		return (NULL);
	map[0] = strdup("1111111");
	map[1] = strdup("1000101");
	map[2] = strdup("1000101");
	map[3] = strdup("1110001");
	map[4] = strdup("1000011");
	map[5] = strdup("1111111");
	map[6] = NULL;
	return (map);
}

void	verif_player_exist(t_game game)
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
				return ;
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
