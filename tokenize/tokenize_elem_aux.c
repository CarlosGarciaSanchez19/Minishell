/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_elem_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:24:30 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/19 15:09:47 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	tokenize_element_aux4(char *elem, t_tokens **former_token,
	char **new_kind)
{
	if (ft_strcmp(*new_kind, "inmediate_heredoc") == 0)
	{
		if ((*former_token)->heredoc_del)
			free((*former_token)->heredoc_del);
		(*former_token)->heredoc_del = ft_strdup(elem + 2);
		if ((*former_token)->heredoc_del == NULL)
			return (100);
		return (0);
	}
	if (ft_strcmp(*new_kind, "inmediate_append") == 0)
	{
		if ((*former_token)->append_output_name)
			free((*former_token)->append_output_name);
		(*former_token)->append_output_name = ft_strdup(elem + 2);
		if ((*former_token)->append_output_name == NULL)
			return (100);
		return (0);
	}
	else
		return (100);
	return (0);
}

/*
	Los 'inmediate' se producen cuando los 'special' no dejan un espacio detrás,
	sino que van unidos al propio nombre del archivo.
	En esos casos, hay que montar ya la string del archivo,
	pero saltándonos los 'specials'.
*/
static int	tokenize_element_aux3(char *elem, t_tokens **former_token,
	char **new_kind)
{
	if (ft_strcmp(*new_kind, "inmediate_input") == 0)
	{
		if ((*former_token)->redir_input_name)
			free((*former_token)->redir_input_name);
		(*former_token)->redir_input_name = ft_strdup(elem + 1);
		if ((*former_token)->redir_input_name == NULL)
			return (100);
		return (0);
	}
	if (ft_strcmp(*new_kind, "inmediate_output") == 0)
	{
		if ((*former_token)->redir_output_name)
			free((*former_token)->redir_output_name);
		(*former_token)->redir_output_name = ft_strdup(elem + 1);
		if ((*former_token)->redir_output_name == NULL)
			return (100);
		return (0);
	}
	return (tokenize_element_aux4(elem, former_token, new_kind));
}

static int	tokenize_element_aux2(char *elem, t_tokens **former_token,
	char **new_kind)
{
	if (ft_strcmp(*new_kind, "heredoc") == 0)
	{
		if ((*former_token)->heredoc_del)
			free((*former_token)->heredoc_del);
		(*former_token)->heredoc_del = ft_strdup(elem);
		if ((*former_token)->heredoc_del == NULL)
			return (100);
		return (0);
	}
	if (ft_strcmp(*new_kind, "append") == 0)
	{
		if ((*former_token)->append_output_name)
			free((*former_token)->append_output_name);
		(*former_token)->append_output_name = ft_strdup(elem);
		if ((*former_token)->append_output_name == NULL)
			return (100);
		return (0);
	}
	return (tokenize_element_aux3(elem, former_token, new_kind));
}

static int	tokenize_element_aux1(char *elem, t_tokens **former_token,
	char **new_kind)
{
	if (ft_strcmp(*new_kind, "input") == 0)
	{
		if ((*former_token)->redir_input_name)
			free((*former_token)->redir_input_name);
		(*former_token)->redir_input_name = ft_strdup(elem);
		if ((*former_token)->redir_input_name == NULL)
			return (100);
		return (0);
	}
	if (ft_strcmp(*new_kind, "output") == 0)
	{
		if ((*former_token)->redir_output_name)
			free((*former_token)->redir_output_name);
		(*former_token)->redir_output_name = ft_strdup(elem);
		if ((*former_token)->redir_output_name == NULL)
			return (100);
		return (0);
	}
	return (tokenize_element_aux2(elem, former_token, new_kind));
}

int	tokenize_element_aux0(char *elem, t_tokens **former_token, char **new_kind)
{
	t_tokens	*new_token;

	if (ft_strcmp(*new_kind, "pipe") == 0)
	{
		(*former_token)->cmd_pipe = 1;
		new_token = new_cmd_token();
		if (new_token == NULL)
			return (100);
		(*former_token)->next = new_token;
		(*former_token) = new_token;
		return (0);
	}
	if (ft_strncmp(*new_kind, "special", 7) == 0)
	{
		(*former_token)->special = 1;
		return (0);
	}
	if (ft_strcmp(*new_kind, "command") == 0)
	{
		(*former_token)->cmd = ft_strdup(elem);
		if ((*former_token)->cmd == NULL)
			return (100);
		return (0);
	}
	return (tokenize_element_aux1(elem, former_token, new_kind));
}
