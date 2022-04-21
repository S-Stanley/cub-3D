/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:15:09 by stan              #+#    #+#             */
/*   Updated: 2022/04/21 01:15:18 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
