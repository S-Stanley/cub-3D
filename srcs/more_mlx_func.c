/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_mlx_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:58:32 by acousini          #+#    #+#             */
/*   Updated: 2022/05/10 23:32:21 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_textures(t_game *game)
{
	game->ea.img = NULL;
	game->so.img = NULL;
	game->no.img = NULL;
	game->we.img = NULL;
}

void	load_textures(t_game *game)
{
	load_texture(game, &game->ea, game->texture_ea);
	load_texture(game, &game->we, game->texture_we);
	load_texture(game, &game->so, game->texture_so);
	load_texture(game, &game->no, game->texture_no);
}
