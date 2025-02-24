/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multiarray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:01:34 by dsoriano          #+#    #+#             */
/*   Updated: 2024/11/18 19:16:51 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_multiarray(void **multiarray)
{
	int	i;

	i = 0;
	while (multiarray[i])
	{
		free(multiarray[i]);
		multiarray[i] = NULL;
		i++;
	}
	free(multiarray);
	multiarray = NULL;
}
