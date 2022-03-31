/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixtures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:51:48 by stan              #+#    #+#             */
/*   Updated: 2022/03/29 21:12:16 by stan             ###   ########.fr       */
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

	if (strcmp(type, "floor") == 0)
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

t_game	init_game(void)
{
	t_game		game;

	game.player_dir = PLAYER_DIR_NO;
	game.texture_no = strdup("assets/texture_no.xpm");
	game.texture_so = strdup("assets/texture_so.xpm");
	game.texture_we = strdup("assets/texture_we.xpm");
	game.texture_ea = strdup("assets/texture_ea.xpm");
	game.floor_color = get_rbg_color("floor");
	game.ceil_color = get_rbg_color("ceil");
	game.map = init_map();
	return (game);
}

void	free_map(char **map)
{
	int		i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game(t_game game)
{
	free(game.texture_no);
	free(game.texture_so);
	free(game.texture_we);
	free(game.texture_ea);
	free_map(game.map);
}
