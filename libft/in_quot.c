/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:54:57 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/03 20:57:48 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_quot(char c, int *quote1, int *quote2)
{
	if (c == '\"' && *quote2 == 0)
	{
		if (*quote1 == 0)
			*quote1 = 1;
		else
			*quote1 = 0;
		return (1);
	}
	if (c == '\'' && *quote1 == 0)
	{
		if (*quote2 == 0)
			*quote2 = 1;
		else
			*quote2 = 0;
		return (1);
	}
	return (0);
}
