/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixtures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:51:48 by stan              #+#    #+#             */
/*   Updated: 2022/05/10 22:54:09 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void	check_multiple_player(t_game game)
{
	int		i;
	int		x;
	int		player_found;

	i = -1;
	player_found = 0;
	while (game.map[++i])
	{
		x = 0;
		while (game.map[i][x])
		{
			if (game.map[i][x] == 'N'
				|| game.map[i][x] == 'W'
				|| game.map[i][x] == 'E'
				|| game.map[i][x] == 'S')
				player_found++;
			x++;
		}
	}
	if (player_found != 1)
	{
		free_game(game);
		printf("Error\nCannot have no more or less than one player in the map\n");
		exit(1);
	}
}

void	verif_map_space(t_game game)
{
	int		i;
	int		x;
	int		start;

	i = 0;
	start = 0;
	while (game.map[i])
	{
		x = 0;
		if (game.map[i][x] == '1')
			start++;
		while (game.map[i][x])
		{
			if (i == 0 && start)
				check_line_closed_top(game, i, x);
			if (!game.map[i + 1])
				check_line_closed_bottom(game, i, x);
			if (i + 1 < count_len_matrice(game.map))
				check_line_closed_right(game, i, x);
			if (x == 0 && start)
				check_line_closed_left(game, i, x);
			x++;
		}
		i++;
	}
}

void	verif_column(t_game game)
{
	int		i;
	int		x;
	int		max;

	i = 0;
	max = 0;
	while (game.map[i])
	{
		x = 0;
		while (game.map[i][x])
		{
			if (x > max && game.map[i][x] != '1' && game.map[i][x] != ' ')
			{
				printf("Error\nThe map is not closed at position:%d %d\n", i, x);
				free_game(game);
				exit(1);
			}
			x++;
		}
		if (x > max)
			max = x;
		i++;
	}
}

char	*affect_line_map(char *line, int len)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i])
	{
		str[i] = line[i];
		i++;
	}
	while (i < len)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = 0;
	return (str);
}

// Ajoutes des espaces
//	pour que la totalite des lignes soient de la meme taille.
char	**refractor_map(char **map, int len)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (count_len_matrice(map) + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != len)
		{
			new_map[i] = affect_line_map(map[i], len);
			if (!new_map[i])
				new_map[i] = map[i];
		}
		else
			new_map[i] = ft_strdup(map[i]);
		i++;
	}
	new_map[i] = 0;
	free_matrice(map);
	return (new_map);
}

int		count_max_len_line(char **map)
{
	int		i;
	int		x;
	int		max;

	i = 0;
	max = -1;
	while (map[i])
	{
		x = 0;
		while (map[i][x])
			x++;
		if (x > max)
			max = x;
		i++;
	}
	return (max);
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
	check_rgb(game);
	check_multiple_player(game);
	game.map = refractor_map(game.map, count_max_len_line(game.map));
	verif_map_config(game);
	verif_map_closed(game);
	verif_map_space(game);
	verif_column(game);
	verif_player_exist(game);
	game.player_dir = verif_player_exist(game);
	verif_player_pos(&game);
	check_err_open_map(game);
	return (game);
}
