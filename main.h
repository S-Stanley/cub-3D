/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:21:01 by stan              #+#    #+#             */
/*   Updated: 2022/03/29 20:57:16 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define PLAYER_DIR_NO	0
# define PLAYER_DIR_SO	1
# define PLAYER_DIR_WE	2
# define PLAYER_DIR_EA	3

typedef struct s_rgb {
	int		color1;
	int		color2;
	int		color3;
}	t_rgb;

typedef struct s_game {
	int		player_dir;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	t_rgb	floor_color;
	t_rgb	ceil_color;
	char	**map;
}	t_game;

char	**init_map(void);
t_rgb	get_rbg_color(char *type);
t_game	init_game(void);
void	free_map(char **map);
void	free_game(t_game game);

#endif