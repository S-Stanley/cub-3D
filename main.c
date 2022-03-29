/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:21:03 by stan              #+#    #+#             */
/*   Updated: 2022/03/29 20:52:59 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	t_game		game;

	game = init_game();
	free_game(game);
	return (0);
}
