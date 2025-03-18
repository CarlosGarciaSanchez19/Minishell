/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:52 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 16:55:39 by carlosg2         ###   ########.fr       */
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

static void	close_redirect_pipe(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

static void	expand_and_write(int fd, char **line, char *og_del, t_shell *shell)
{
	if (!ft_strhasdoublequote(og_del) && !ft_strhassimplequote(og_del))
		expand_env_vars(line, *shell);
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
}

void	heredoc(t_tokens *tokens, t_shell *shell, char *str)
{
	char	*line;
	int		fd[2];
	char	*orig_del;

	orig_del = shell->orig_input[tokens->del_pos];
	rl_event_hook = event;
	signal(SIGINT, sigint_handler_heredoc);
	if (pipe(fd) < 0)
		error_pipe(tokens, shell);
	if (str)
		write(fd[1], str, ft_strlen(str));
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, "") || !ft_strcmp(line, tokens->heredoc_del))
		{
			free(line);
			break ;
		}
		expand_and_write(fd[1], &line, orig_del, shell);
		free(line);
	}
	close_redirect_pipe(fd);
}
