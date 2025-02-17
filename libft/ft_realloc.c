/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:03:54 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/17 11:00:04 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;
	size_t	ptrsize;

	if (ptr == 0)
		return (malloc(size));
	ptrsize = sizeof(ptr);
	if (size <= ptrsize)
		return (ptr);
	newptr = malloc(size);
	ft_memcpy(newptr, ptr, ptrsize);
	free(ptr);
	return (newptr);
}
