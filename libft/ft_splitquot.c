/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:03:33 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/10 12:51:58 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	in_quot(char c, int *quote1, int *quote2)
{
	if (c == '\"' && *quote2 == 0)
	{
		if (*quote1 == 0)
			*quote1 = 1;
		else
			*quote1 = 0;
	}
	if (c == '\'' && *quote1 == 0)
	{
		if (*quote2 == 0)
			*quote2 = 1;
		else
			*quote2 = 0;
	}
}

static int	countquot_words(char const *str, char c)
{
	int	count;
	int	in_word;
	int	quote1;
	int	quote2;

	count = 0;
	in_word = 0;
	quote1 = 0;
	quote2 = 0;
	while (*str)
	{
		if (*str == c && (quote1 == 0 || quote2 == 0))
			in_word = 0;
		else if (in_word == 0)
		{
			count++;
			in_word = 1;
		}
		in_quot(*str, &quote1, &quote2);
		str++;
	}
	return (count);
}

int	ft_modquotstrlen(char const *str, char c)
{
	int	i;
	int	quote1;
	int	quote2;

	i = 0;
	quote1 = 0;
	quote2 = 0;
	while (str[i] && str[i] != c)
	{
		in_quot(str[i], &quote1, &quote2);
		i++;
		if (str[i] == c && (quote1 == 1 || quote2 == 1))
			i++;
	}
	return (i);
}

static char	*create_string(char const *str, char c)
{
	char	*string;
	int		i;
	int		quote1;
	int		quote2;

	string = malloc(ft_modquotstrlen(str, c) + 1);
	if (!string)
		return (NULL);
	quote1 = 0;
	quote2 = 0;
	i = 0;
	while (*str && *str != c)
	{
		in_quot(*str, &quote1, &quote2);
		string[i++] = *str;
		str++;
		if (*str == c && (quote1 == 1 || quote2 == 1))
		{
			string[i++] = *str;
			str++;
		}
	}
	string[i] = '\0';
	return (string);
}

char	**ft_splitquot(char const *str, char c)
{
	char	**array;
	int		arr_idx;
	char	*string;

	arr_idx = 0;
	array = (char **)malloc((countquot_words(str, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			string = create_string(str, c);
			if (!string)
				return (ft_freearray(array, arr_idx), NULL);
			array[arr_idx] = string;
			arr_idx++;
			str += ft_modstrlen(str, c);
		}
	}
	array[arr_idx] = NULL;
	return (array);
}
