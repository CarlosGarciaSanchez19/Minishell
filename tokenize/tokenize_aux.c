/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:01:04 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/19 15:39:43 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*search_for_kind_aux1(char *former_kind)
{
	if (former_kind == NULL || ft_strcmp(former_kind, "pipe") == 0)
		return ("command");
	if (ft_strcmp(former_kind, "special_input") == 0)
		return ("input");
	if (ft_strcmp(former_kind, "special_output") == 0)
		return ("output");
	if (ft_strcmp(former_kind, "special_heredoc") == 0)
		return ("heredoc");
	if (ft_strcmp(former_kind, "special_append") == 0)
		return ("append");
	else
		return ("argument");
}

static char	*search_for_kind_aux0(int i, char *former_kind, t_shell *shell)
{
	if (shell->user_input[i][0] == '>' && !ft_strisquote(shell->orig_input[i]))
	{
		if (shell->user_input[i][1] == '\0')
			return ("special_output");
		if (shell->user_input[i][1] == '>' && shell->user_input[i][2] == '\0')
			return ("special_append");
		if (shell->user_input[i][1] == '>')
			return ("inmediate_append");
		else
			return ("inmediate_output");
	}
	else
		return (search_for_kind_aux1(former_kind));
}

/*
	Recorremos el elemento para determinar que tipo de input es.
*/
char	*search_for_kind(int i, char *former_kind, t_shell *shell)
{
	if (shell->user_input[i][0] == '|' && shell->user_input[i][1] == '\0')
		return ("pipe");
	if (shell->user_input[i][0] == '<' && !ft_strisquote(shell->orig_input[i]))
	{
		if (shell->user_input[i][1] == '\0')
			return ("special_input");
		if (shell->user_input[i][1] == '<' && shell->user_input[i][2] == '\0')
			return ("special_heredoc");
		if (shell->user_input[i][1] == '<')
			return ("inmediate_heredoc");
		else
			return ("inmediate_input");
	}
	else
		return (search_for_kind_aux0(i, former_kind, shell));
}

t_tokens	*new_cmd_token(void)
{
	t_tokens	*token;

	token = ft_calloc(1, sizeof(t_tokens));
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}
