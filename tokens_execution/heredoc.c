/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:52 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/20 14:21:51 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	ft_printf("^C\n");
	rl_event_hook = NULL;
}

void	heredoc(char *delimiter)
{
	char	*line;
	int		tmp_fd;
	struct sigaction sa_new, sa_old;

	sa_new.sa_handler = &sigint_handler_heredoc;
    sa_new.sa_flags = 0;
    sigemptyset(&sa_new.sa_mask);
    sigaction(SIGINT, &sa_new, &sa_old);
	tmp_fd = open("/tmp/here_doc", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			line = NULL;
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	sigaction(SIGINT, &sa_old, NULL);
	close(tmp_fd);
	tmp_fd = open("/tmp/here_doc", O_RDONLY);
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}
