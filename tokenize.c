/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/19 14:01:32 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	En cada 'elem' sacamos su tipo como string,
	y hacemos cosas distintas en función del tipo.
*/
static int	tokenize_elem(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	*new_kind = search_for_kind(elem, *new_kind);
	if (ft_strcmp(*new_kind, "argument") == 0)
	{
		if (*arg_n == 0)
			(*former_token)->cmd_args = malloc(sizeof(char *) * (*arg_n + 2));
		else
			(*former_token)->cmd_args = ft_realloc((*former_token)->cmd_args,
					sizeof(char *) * (*arg_n + 1),
					sizeof(char *) * (*arg_n + 2));
		(*former_token)->cmd_args[*arg_n] = ft_strdup(elem);
		if ((*former_token)->cmd_args[*arg_n] == NULL)
			return (100);
		(*former_token)->cmd_args[*arg_n + 1] = NULL;
		(*arg_n)++;
		return (0);
	}
	*arg_n = 0;
	return (tokenize_element_aux0(elem, former_token, new_kind));
}

static int	check_special_valid(t_tokens *start_token)
{
	t_tokens	*current_token;

	current_token = start_token;
	while (current_token)
	{
		if (current_token->special && !current_token->redir_input_name
			&& !current_token->redir_output_name && !current_token->heredoc_del
			&& !current_token->append_output_name)
		{
			ft_printf("syntax error near unexpected token `newline'\n");
			return (0);
		}
		current_token = current_token->next;
	}
	return (1);
}

static void	check_exit_status(t_tokens *start_token, t_shell *shell)
{
	if (shell->exit_status == 100)
	{
		free_tokens(start_token);
		free_shell(shell);
		exit(100);
	}
}

static int	aux_initvars_tokenize(char **new_kind, int *arg_n,
	t_tokens **former_token, t_tokens **start_token)
{
	*new_kind = NULL;
	*arg_n = 0;
	*former_token = new_cmd_token();
	*start_token = *former_token;
	return (0);
}

/*
	Recorremos el array del input y vamos tokenizando en lista enlazada.
	Si es el primer elemento lo guardamos como el "start" de la lista.
	El "former" token lo vamos actualizando cuando hay un nuevo comando,
	y reenviando en cada iteración para que rellenar su contenido.
*/
t_tokens	*tokenize_everything(t_shell *shell)
{
	int			i;
	int			arg_n;
	char		*new_kd;
	t_tokens	*f_token;
	t_tokens	*st_token;

	i = aux_initvars_tokenize(&new_kd, &arg_n, &f_token, &st_token);
	while (shell->user_input[i])
	{
		if (check_quotes(st_token, i, shell))
			return (NULL);
		if (new_kd && (!ft_strcmp(new_kd, "special_heredoc")
				|| !ft_strncmp(shell->user_input[i], "<<", 2)))
			f_token->del_pos = i;
		else if (!ft_strhassimplequote(shell->orig_input[i]))
			expand_env_vars(&(shell->user_input[i]), *shell);
		if (shell->user_input[i] && shell->user_input[i][0])
			if (tokenize_elem(shell->user_input[i], &f_token, &arg_n, &new_kd))
				shell->exit_status = 100;
		check_exit_status(st_token, shell);
		i++;
	}
	if (!check_special_valid(st_token))
		return (free_tokens(st_token), NULL);
	return (st_token);
}
