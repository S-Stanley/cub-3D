/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixtures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:51:48 by stan              #+#    #+#             */
/*   Updated: 2022/04/29 22:21:46 by stan             ###   ########.fr       */
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

void	check_rgb(t_game game)
{
	int		err;

	err = 0;
	if (game.ceil_color.color1 > 255 || game.ceil_color.color1 < 0)
		err = 1;
	if (game.ceil_color.color2 > 255 || game.ceil_color.color2 < 0)
		err = 1;
	if (game.ceil_color.color3 > 255 || game.ceil_color.color3 < 0)
		err = 1;
	if (game.floor_color.color1 > 255 || game.floor_color.color1 < 0)
		err = 1;
	if (game.floor_color.color2 > 255 || game.floor_color.color2 < 0)
		err = 1;
	if (game.floor_color.color3 > 255 || game.floor_color.color3 < 0)
		err = 1;
	if (err)
	{
		free_game(game);
		printf("Error\nRGB color should be between 0 and 255\n");
		exit(1);
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

void	check_line_closed_top(t_game game, int i, int x)
{
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i + 1][x - 1] != '1' || game.map[i + 1][x + 1] != '1')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i + 1][x] == ' ')
		{
			check_line_closed_top(game, i + 1, x);
		}
		if (game.map[i + 1][x] == '1')
			return ;
	}
}

void	check_line_closed_bottom(t_game game, int i, int x)
{
	if (game.map[i][x] == ' ')
	{
		if (game.map[i - 1][x] == '0' || game.map[i - 1][x - 1] != '1' || game.map[i - 1][x + 1] != '1')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i - 1][x] == ' ')
		{
			check_line_closed_bottom(game, i - 1, x);
		}
		if (game.map[i - 1][x] == '1')
			return ;
	}
}

void	check_line_closed_right(t_game game, int i, int x)
{
	if (game.map[i][x + 1] != 0)
		return ;
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i - 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i][x - 1] == ' ')
			check_line_closed_right(game, i, x - 1);
		if (game.map[i][x - 1] == '1')
			return ;
	}
}

void	check_line_closed_left(t_game game, int i, int x)
{
	if (game.map[i][x] == ' ')
	{
		if (game.map[i + 1][x] == '0' || game.map[i - 1][x] == '0')
		{
			printf("Error\nThe map is not closed at position %d %d\n", i, x);
			free_game(game);
			exit(1);
		}
		if (game.map[i][x + 1] == ' ')
			check_line_closed_left(game, i, x + 1);
		if (game.map[i][x + 1] == '1')
			return ;
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
	verif_map_space(game);
	verif_column(game);
	verif_player_exist(game);
	game.player_dir = verif_player_exist(game);
	verif_player_pos(&game);
	check_rgb(game);
	check_multiple_player(game);
	return (game);
}
