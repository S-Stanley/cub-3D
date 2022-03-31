/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stan <stan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:34:45 by stan              #+#    #+#             */
/*   Updated: 2022/03/30 20:38:19 by stan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
