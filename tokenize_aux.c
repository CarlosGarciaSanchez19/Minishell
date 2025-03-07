/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:01:04 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/07 15:16:34 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	special_postchecker()
{
} */

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

static char	*search_for_kind_aux0(char *elem, char *former_kind)
{
	if (elem[0] == '>')
	{
		if (elem[1] == '\0')
		{
//			special_postchecker();
			return ("special_output");
		}
		if (elem[1] == '>' && elem[2] == '\0')
		{
//			special_postchecker();
			return ("special_append");
		}
		if (elem[1] == '>')
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
char	*search_for_kind(char *elem, char *former_kind)
{
	//printf("former_kind: %s\n", former_kind);
	if (elem[0] == '|' && elem[1] == '\0')
		return ("pipe");
	if (elem[0] == '<')
	{
		if (elem[1] == '\0')
		{
//			special_postchecker();
			return ("special_input");
		}
		if (elem[1] == '<' && elem[2] == '\0')
		{
//			special_postchecker();
			return ("special_heredoc");
		}
		if (elem[1] == '<')
			return ("inmediate_heredoc");
		else
			return ("inmediate_input");
	}
	else
		return (search_for_kind_aux0(elem, former_kind));
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
