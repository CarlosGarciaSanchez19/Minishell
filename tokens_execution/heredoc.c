/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:52 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/24 20:20:42 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_printf("^C\n");
	rl_done = 1;
} */


void	heredoc(char *delimiter)
{
	char	*line;
	int		fd[2];
	/* struct sigaction sa_new, sa_old;

	sa_new.sa_handler = &sigint_handler_heredoc;
    sa_new.sa_flags = 0;
    sigemptyset(&sa_new.sa_mask);
    sigaction(SIGINT, &sa_new, &sa_old); */
	rl_catch_signals = 1;
	if (pipe(fd) < 0)
	{
		ft_printf("Error: Pipe could not be created\n");
		exit(1);
	}
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
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
/* 	sigaction(SIGINT, &sa_old, NULL); */
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
