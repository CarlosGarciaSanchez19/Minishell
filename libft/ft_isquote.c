/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:06:38 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/18 15:46:37 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	ft_strisquote(char *str)
{
	if ((str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		|| (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
		return (1);
	return (0);
}

int	ft_strissimplequote(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (1);
	return (0);
}

int	ft_strhassimplequote(char *str)
{
	int	simple_quot;
	int	double_quot;
	int	i;
	int	has_simple;

	simple_quot = 0;
	double_quot = 0;
	has_simple = 0;
	i = 0;
	while (str && str[i])
	{
		if (in_quot(str[i], &double_quot, &simple_quot) && simple_quot)
			has_simple = 1;
		i++;
	}
	if (simple_quot || double_quot)
		return (-1);
	return (has_simple);
}

int	ft_strisdoublequote(char *str)
{
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (1);
	return (0);
}

int	ft_strhasdoublequote(char *str)
{
	int	simple_quot;
	int	double_quot;
	int	i;
	int	has_double;

	simple_quot = 0;
	double_quot = 0;
	has_double = 0;
	i = 0;
	while (str && str[i])
	{
		if (in_quot(str[i], &double_quot, &simple_quot) && double_quot)
			has_double = 1;
		i++;
	}
	if (double_quot || simple_quot)
		return (-1);
	return (has_double);
}
