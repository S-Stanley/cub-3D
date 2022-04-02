/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:21:01 by stan              #+#    #+#             */
/*   Updated: 2022/04/02 17:26:12 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# include "../libft/libft.h"

# define PLAYER_DIR_NO		0
# define PLAYER_DIR_SO		1
# define PLAYER_DIR_WE		2
# define PLAYER_DIR_EA		3
# define KEY_UP				119
# define KEY_LEFT			97
# define KEY_RIGHT			100
# define KEY_DOWN			115

typedef struct	s_rgb
{
	int		color1;
	int		color2;
	int		color3;
}				t_rgb;

typedef struct	s_text
{
	void	*img;
	char	*addr;
	int		init;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_text;

typedef struct	s_point
{
	float	x;
	float	y;
}				t_point;

typedef struct	s_info
{
	int		height;
	int		width;
}				t_info;

typedef struct	raycast
{
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
	float	sideDistX;
	float	sideDistY;
	float	rayDirX;
	float	rayDirY;
	float	cameraX;
	float	cameraY;
	int		stepX;
	int		stepY;
	int		hit;
	int		sideHit;
}				raycast;

typedef struct	s_game 
{
	void	*mlx;
	void	*win;
	raycast	*player;
	t_text	*wall2d;
	t_text	*floor2d;
	t_text	dot;
	char	**map;
	int		player_dir;
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	t_rgb	floor_color;
	t_rgb	ceil_color;
	char	**map2; // map temporaire plus grande 
}				t_game;

char	**init_map(void);
t_rgb	get_rbg_color(char *type);
t_game	init_game(char *filename);
void	free_map(char **map);
void	free_game(t_game game);

bool	ft_strcmp(char *s1, char *s2);
int		find_index(char *str, char *to_find);
int		count_occurence(char *str, char to_count);
char	*ft_trim(char *str, char to_trim);

int		find_last_index(char *str, char to_find);

void	check_args(int ac, char **av);

t_game	get_texture(t_game game, char *filename);

char	*get_line(int fd);

#endif