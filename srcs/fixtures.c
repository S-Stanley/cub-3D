/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixtures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:51:48 by stan              #+#    #+#             */
/*   Updated: 2022/04/03 17:11:26 by sserbin          ###   ########.fr       */
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

t_rgb	get_rbg_color(char *type)
{
	t_rgb	rgb;

	if (ft_strcmp(type, "floor") == 0)
	{
		rgb.color1 = 220;
		rgb.color2 = 100;
		rgb.color3 = 0;
		return (rgb);
	}
	rgb.color1 = 225;
	rgb.color2 = 30;
	rgb.color3 = 0;
	return (rgb);
}

t_game	init_game(char *filename)
{
	t_game		game;

	game.player_dir = PLAYER_DIR_NO;
	game.floor_color = get_rbg_color("floor");
	game.ceil_color = get_rbg_color("ceil");
	game.map = parse_map(filename);
	if (!game.map)
	{
		printf("Error\nMap parsing failed\n");
		exit(1);
	}
	game = get_texture(game, filename);
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
