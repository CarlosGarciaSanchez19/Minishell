/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_elem_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:24:30 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/21 16:49:13 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*tokenize_element_aux4(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	if (ft_strcmp(*new_kind, "inmediate_heredoc") == 0)
	{
		(*former_token)->heredoc_del = ft_strdup(elem + 2);
		if ((*former_token)->heredoc_del == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "inmediate_append") == 0)
	{
		(*former_token)->append_output_name = ft_strdup(elem + 2);
		if ((*former_token)->append_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	else
	{
		//En caso de invalid habrá que dar error
//		printf("placeholder: error! ... invalid arg");
		exit(1);
	}
	return (arg_n);
}

/*
	Los 'inmediate' se producen cuando los 'special' no dejan un espacio detrás,
	sino que van unidos al propio nombre del archivo.
	En esos casos, hay que montar ya la string del archivo,
	pero saltándonos los 'specials'.
*/
static int	*tokenize_element_aux3(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	if (ft_strcmp(*new_kind, "inmediate_input") == 0)
	{
		(*former_token)->redir_input_name = ft_strdup(elem + 1);
		if ((*former_token)->redir_input_name == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "inmediate_output") == 0)
	{
		(*former_token)->redir_output_name = ft_strdup(elem + 1);
		if ((*former_token)->redir_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	return (tokenize_element_aux4(elem, former_token, arg_n, new_kind));
}

static int	*tokenize_element_aux2(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	if (ft_strcmp(*new_kind, "heredoc") == 0)
	{
		(*former_token)->heredoc_del = ft_strdup(elem);
		if ((*former_token)->heredoc_del == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "append") == 0)
	{
		(*former_token)->append_output_name = ft_strdup(elem);
		if ((*former_token)->append_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	return (tokenize_element_aux3(elem, former_token, arg_n, new_kind));
}

static int	*tokenize_element_aux1(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	if (ft_strcmp(*new_kind, "input") == 0)
	{
		(*former_token)->redir_input_name = ft_strdup(elem);
		if ((*former_token)->redir_input_name == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "output") == 0)
	{
//		printf("Estamos en Output!!\n");
		(*former_token)->redir_output_name = ft_strdup(elem);
		if ((*former_token)->redir_output_name == NULL)
			exit (1);
//		printf("estamos en el token: %p\n", (*former_token));
		return (arg_n);
	}
	return (tokenize_element_aux2(elem, former_token, arg_n, new_kind));
}

int	*tokenize_element_aux0(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	t_tokens	*new_token;

	if (ft_strcmp(*new_kind, "pipe") == 0)
	{
		(*former_token)->cmd_pipe = 1;
		new_token = new_cmd_token();
		if (new_token == NULL)
			exit (1);
		(*former_token)->next = new_token;
		(*former_token) = new_token;
		return (arg_n);
	}
	if (ft_strncmp(*new_kind, "special", 7) == 0)
		return (arg_n);
	if (ft_strcmp(*new_kind, "command") == 0)
	{
		(*former_token)->cmd = ft_strdup(elem);
		if ((*former_token)->cmd == NULL)
			exit (1);
		return (arg_n);
	}
	return (tokenize_element_aux1(elem, former_token, arg_n, new_kind));
}
