/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:03:54 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/26 20:23:03 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	char	*newptr;

	if (ptr == 0)
		return (malloc(size));
	if (size <= old_size)
		return (ptr);
	newptr = malloc(size);
	ft_memcpy(newptr, ptr, old_size);
	free(ptr);
	return (newptr);
}
