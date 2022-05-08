/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:02 by acousini          #+#    #+#             */
/*   Updated: 2022/05/08 19:11:06 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	close_win_hook(int keycode, t_game *game)
{
	(void)keycode;
	free_game_point(game);
	exit (0);
	return (1);
}

int	close_win_hook_cross(t_game *game)
{
	free_game_point(game);
	exit (0);
	return (1);
}

int	key_press_hook(int keycode, t_game *game)
{
	if (keycode == KEY_UP)
		game->hooks.north = 1;
	if (keycode == ARROW_LEFT)
		game->hooks.rotate_west = 1;
	if (keycode == ARROW_RIGHT)
		game->hooks.rotate_east = 1;
	if (keycode == KEY_DOWN)
		game->hooks.south = 1;
	if (keycode == KEY_LEFT)
		game->hooks.west = 1;
	if (keycode == KEY_RIGHT)
		game->hooks.east = 1;
	if (keycode == 65307)
	{
		close_win_hook(1, game);
		free_game_point(game);
	}
	return (keycode);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode == KEY_UP)
		game->hooks.north = 0;
	if (keycode == ARROW_LEFT)
		game->hooks.rotate_west = 0;
	if (keycode == ARROW_RIGHT)
		game->hooks.rotate_east = 0;
	if (keycode == KEY_DOWN)
		game->hooks.south = 0;
	if (keycode == KEY_LEFT)
		game->hooks.west = 0;
	if (keycode == KEY_RIGHT)
		game->hooks.east = 0;
	return (1);
}
