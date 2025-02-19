/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:52 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/19 17:39:33 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(char *delimiter)
{
	char	*line;
	int		tmp_fd;
	
	tmp_fd = open("/tmp/here_doc", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	line = readline("> ");
	while (line && ft_strcmp(line, delimiter))
	{
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		line = readline("> ");
	}
	close(tmp_fd);
	tmp_fd = open("/tmp/here_doc", O_RDONLY);
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}
