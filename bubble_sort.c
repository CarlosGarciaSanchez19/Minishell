/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:36:54 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/05 19:45:46 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort(char **arr)
{
	int		i;
	int		j;
	int		size;
	char	*temp;

	size = ft_arraylen(arr);
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
