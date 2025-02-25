/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:52 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/25 18:50:26 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	event(void)
{
	return (rl_done);
}

static void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	ft_printf("^C");
	rl_done = 1;
}

void	heredoc(t_tokens *tokens, t_shell *shell)
{
	char	*line;
	int		fd[2];

	rl_event_hook = event;
	signal(SIGINT, sigint_handler_heredoc);
	if (pipe(fd) < 0)
		error_pipe(tokens, shell);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, "")
			|| !ft_strcmp(line, tokens->heredoc_del))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
