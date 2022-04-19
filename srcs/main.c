/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:21:03 by stan              #+#    #+#             */
/*   Updated: 2022/04/16 19:12:48 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	t_game		game;

	check_args(ac, av);
	check_config_file(av[1]);
	game = init_game(av[1]);
	init_info(&game);
	init_mlx(game);
	free_game(game);
	return (0);
}
