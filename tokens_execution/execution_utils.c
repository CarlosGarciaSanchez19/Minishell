/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:21:55 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/26 19:36:37 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = 0;
	command = malloc(sizeof(char *) * (ft_arraylen(tokens->cmd_args) + 2));
	if (!command)
	{
		ft_printf("Error: Command array could not be created\n");
		exit(1);
	}
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
