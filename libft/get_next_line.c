/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 12:20:23 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/19 12:20:46 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

static char	*strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (s1)
		s1_len = ft_strlen(s1);
	else
		s1_len = 0;
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(s1_len + s2_len + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		ft_strcpy(new_str, s1);
	ft_strcpy(new_str + s1_len, s2);
	free(s1);
	return (new_str);
}

static int	find_nl(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*process_nl_stash(char **stash)
{
	char	*tmp;
	char	*line;
	int		nl;

	line = NULL;
	nl = find_nl(*stash);
	if (*stash && **stash)
	{
		if (nl != -1)
		{
			line = ft_strndup(*stash, nl + 1);
			tmp = ft_strndup(*stash + nl + 1, ft_strlen(*stash + nl + 1));
			free(*stash);
			*stash = tmp;
		}
		else
		{
			line = ft_strndup(*stash, ft_strlen(*stash));
			free(*stash);
		}
	}
	else if (*stash && !**stash)
		free(stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (find_nl(stash) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash),
				free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = strjoin_free(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (process_nl_stash(&stash));
}
