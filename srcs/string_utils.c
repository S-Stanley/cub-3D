/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:33:44 by stan              #+#    #+#             */
/*   Updated: 2022/04/21 01:13:27 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	ft_strcmp(char *s1, char *s2)
{
	int		i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	find_index(char *str, char *to_find)
{
	int		i;
	int		buff;
	int		x;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		buff = i;
		x = 0;
		while (to_find[x] && str[i] && str[i] == to_find[x])
		{
			i++;
			x++;
		}
		if (x == (int)ft_strlen(to_find))
			return (buff);
		i = buff;
		i++;
	}
	return (-1);
}

int	count_occurence(char *str, char to_count)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == to_count)
			count++;
		i++;
	}
	return (count);
}

char	*ft_trim(char *str, char to_trim)
{
	int		i;
	char	*to_return;
	int		x;

	if (!str)
		return (NULL);
	i = 0;
	x = 0;
	to_return = malloc(sizeof(char)
			* (ft_strlen(str) - count_occurence(str, to_trim) + 1));
	while (str[i])
	{
		if (str[i] != to_trim)
		{
			to_return[x] = str[i];
			x++;
		}
		i++;
	}
	to_return[x] = 0;
	free(str);
	return (to_return);
}

char	*ft_concat(char *s1, char *s2)
{
	int		i;
	int		x;
	char	*to_return;

	if (!s2)
		return (NULL);
	i = 0;
	x = -1;
	to_return = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!to_return)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			to_return[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++x])
		to_return[i++] = s2[x];
	to_return[i] = 0;
	free(s2);
	return (to_return);
}
