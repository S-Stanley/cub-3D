/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:30:02 by acousini          #+#    #+#             */
/*   Updated: 2022/04/15 17:10:36 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

	// clean_struct_game(game, "success");
int	close_win_hook(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	exit (0);
	return (1);
}

int	key_press_hook(int keycode, t_game *game)
{
	if (keycode != KEY_DOWN || keycode != KEY_RIGHT
		|| keycode != KEY_LEFT || keycode != KEY_UP)
	{
		moves(game, keycode);
		raycasting(game, game->plr);
		draw_map_2d(game, -1, -1);
	}
	if (keycode == 65307)
	{
		puts("bye");
		close_win_hook(1, game);
	}
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (keycode != KEY_DOWN || keycode != KEY_RIGHT
		|| keycode != KEY_LEFT || keycode != KEY_UP)
	{
		moves(game, keycode);
		raycasting(game, game->plr);
		draw_map_2d(game, -1, -1);
	}
	return (0);
}
