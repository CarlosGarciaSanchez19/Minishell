/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multiarray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:01:34 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/20 16:09:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_multiarray(void **multiarray)
{
	int	i;

	i = 0;
	while (multiarray && multiarray[i])
	{
		free(multiarray[i]);
		multiarray[i] = NULL;
		i++;
	}
	if (multiarray)
		free(multiarray);
	multiarray = NULL;
}
