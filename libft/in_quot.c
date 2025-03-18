/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:54:57 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/18 15:37:25 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_quot(char c, int *double_quot, int *simple_quot)
{
	if (c == '\"' && *simple_quot == 0)
	{
		if (*double_quot == 0)
			*double_quot = 1;
		else
			*double_quot = 0;
		return (1);
	}
	if (c == '\'' && *double_quot == 0)
	{
		if (*simple_quot == 0)
			*simple_quot = 1;
		else
			*simple_quot = 0;
		return (1);
	}
	return (0);
}
