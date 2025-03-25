/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:21:55 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/25 21:13:19 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec_vars(t_tokens *tokens, int (*pipes)[2])
{
	if (tokens)
		free_tokens(tokens);
	if (pipes)
		free(pipes);
}

int	init_exec_vars_and_pipe_creat(t_tokens *tkns, t_pipes *p, t_shell *shell)
{
	if (!tkns)
		return (102);
	p->num_pipes = tkn_lst_size(tkns) - 1;
	p->pipes = malloc(sizeof(int [2]) * p->num_pipes);
	if (!p->pipes)
	{
		free_tokens(tkns);
		free_shell(shell);
		exit(100);
	}
	create_pipes(p, tkns, shell);
	return (0);
}

int	tkn_lst_size(t_tokens *tkn)
{
	int		i;

	i = 0;
	while (tkn)
	{
		i++;
		tkn = tkn->next;
	}
	return (i);
}

char	**create_command_array(t_tokens *tokens)
{
	char	**command;
	int		i;

	command = malloc(sizeof(char *) * (ft_arraylen(tokens->cmd_args) + 2));
	if (!command)
	{
		free_tokens(tokens);
		exit(100);
	}
	i = 0;
	command[i] = tokens->cmd;
	i++;
	while (tokens->cmd_args && tokens->cmd_args[i - 1])
	{
		command[i] = tokens->cmd_args[i - 1];
		i++;
	}
	command[i] = NULL;
	return (command);
}
