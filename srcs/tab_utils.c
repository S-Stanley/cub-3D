/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sserbin <sserbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:34:45 by stan              #+#    #+#             */
/*   Updated: 2022/04/03 15:20:45 by sserbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	find_last_index(char *str, char to_find)
{
	int		i;
	int		index;

	i = 0;
	if (!str)
		return (-1);
	index = -1;
	while (str[i])
	{
		if (str[i] == to_find)
			index = i;
		i++;
	}
	return (index);
}

int	count_len_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return (0);
	while (matrice[i])
		i++;
	return (i);
}

void	free_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

void	print_matrice(char **matrice)
{
	int		i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		printf("%s\n", matrice[i]);
		i++;
	}
}

char	**push_arr(char **arr, char *to_add)
{
	char	**to_return;
	int		i;

	to_return = malloc(sizeof(char *) * (count_len_matrice(arr) + 2));
	if (!to_return)
		return (NULL);
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			to_return[i] = arr[i];
			i++;
		}
		free(arr);
	}
	to_return[i] = to_add;
	to_return[++i] = 0;
	return (to_return);
}
