/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:21:01 by stan              #+#    #+#             */
/*   Updated: 2022/04/06 18:13:33 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

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

typedef struct	text
{
	void	*img;
	char	*addr;
	int		init;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				text;

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
	t_text	*dot;
	text	pixel;
	t_info	info;
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
char	**parse_map(char *filename);
bool	is_line_map(char *line);

bool	ft_strcmp(char *s1, char *s2);
int		find_index(char *str, char *to_find);
int		count_occurence(char *str, char to_count);
char	*ft_trim(char *str, char to_trim);

int		find_last_index(char *str, char to_find);
int		count_len_matrice(char **matrice);
char	**push_arr(char **arr, char *to_add);
void	free_matrice(char **matrice);
void	print_matrice(char **matrice);

void	*handle_err(char *message, char *to_free);

void	check_args(int ac, char **av);
void	check_config_file(char *filename);

t_game	get_texture(t_game game, char *filename);

void	init_mlx(t_game game);
int		key_press_hook(int keycode, t_game *game);
int		key_release_hook(int keycode, t_game *game);
void	moves(t_game *game, int direction);
int		draw_map_2d(t_game *game, int i, int j);
void	draw_dir(t_game *game, raycast *player);
int		close_win_hook(int keycode, t_game *game);
void	my_mlx_pixel_put(t_text	*data, int x, int y, int color);

char	*get_line(int fd);

#endif