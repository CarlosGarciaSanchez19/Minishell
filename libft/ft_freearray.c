/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:04:18 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/10 15:06:38 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearray(char **array, int arr_len)
{
	while (arr_len >= 0)
	{
		free(array[arr_len]);
		array[arr_len] = NULL;
		arr_len--;
	}
	free(array);
	array = NULL;
}
