/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:10:08 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/13 12:26:36 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*ft_gnlfree(char **var)
{
	if (*var)
	{
		free(*var);
		*var = NULL;
	}
	return (NULL);
}

char	*ft_modstrjoin(char **s1, char *s2)
{
	int			s1len;
	int			s2len;
	int			i;
	char		*str;

	s1len = ft_gnlstrlen(*s1, 0, 1);
	s2len = ft_gnlstrlen(s2, 0, 1);
	str = malloc(s1len + s2len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s1len + s2len)
	{
		if (i < s1len)
			str[i] = (*s1)[i];
		else
			str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	ft_gnlfree(s1);
	free(s2);
	return (str);
}

int	ft_gnlstrlen(char *str, char c, int flag)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	if (flag)
		return (i);
	else
		return (-1);
}

char	*ft_modstrdup(char *src)
{
	char	*newstr;
	int		i;

	if (!src)
		return (NULL);
	i = ft_gnlstrlen(src, 0, 1);
	newstr = (char *)ft_calloc(i + 1, 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (src[i])
	{
		newstr[i] = src[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
