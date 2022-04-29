/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:15:09 by stan              #+#    #+#             */
/*   Updated: 2022/04/29 17:19:31 by acousini         ###   ########.fr       */
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

void	clean_mlx(void *mlx)
{
	mlx_destroy_display(mlx);
	mlx_loop_end(mlx);
	free(mlx);
}

void	clean_struct_texture(void *mlx, t_text texture)
{
	if (texture.img)
		mlx_destroy_image(mlx, texture.img);
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
	if (game)
	{
		clean_struct_texture(game->mlx, game->ea);
		clean_struct_texture(game->mlx, game->we);
		clean_struct_texture(game->mlx, game->so);
		clean_struct_texture(game->mlx, game->no);
		clean_struct_texture(game->mlx, game->pixel);
		clean_struct_texture(game->mlx, game->minimap);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
			clean_mlx(game->mlx);
		if (game->plr)
			free(game->plr);
	}
	free_matrice(game->map);
}
