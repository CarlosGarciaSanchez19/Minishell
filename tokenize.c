/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/11 18:10:19 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Recorremos el elemento para determinar que tipo de input es.
*/
char	*search_for_kind(char *elem, char *former_kind)
{
	printf("former_kind: %s\n", former_kind);
	if (elem[0] == '|' && elem[1] == '\0')
		return ("pipe");
	if (elem[0] == '<')
	{
		if (elem[1] == '\0')
			return ("special_input");
		if (elem[1] == '<' && elem[2] == '\0')
			return ("special_heredoc");
		if (elem[1] == '<')
			return ("inmediate_heredoc");
		else
			return ("inmediate_input");
	}
	if (elem[0] == '>')
	{
		if (elem[1] == '\0')
			return ("special_output");
		if (elem[1] == '>' && elem[2] == '\0')
			return ("special_append");
		if (elem[1] == '>')
			return ("inmediate_append");
		else
			return ("inmediate_output");
	}
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

t_tokens	*new_cmd_token()
{
	t_tokens	*token;

	token = ft_calloc(1, sizeof(t_tokens));
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

/*
	En cada 'elem' sacamos su tipo como string y hacemos cosas distintas en función del tipo
*/
int	*tokenize_element(char *elem, t_tokens *former_token, int *arg_n, char **new_kind)
{
	t_tokens	*new_token;

	*new_kind = search_for_kind(elem, *new_kind);
/* 	printf("elem: %s\n", elem);
	printf("new_kind: %s\n", *new_kind); */
	if (ft_strcmp(*new_kind, "argument") == 0)
	{
		if (*arg_n == 0)
			former_token->cmd_args = malloc(sizeof(char *) * (*arg_n + 2));
		else
			former_token->cmd_args = realloc(former_token->cmd_args, sizeof(char *) * (*arg_n + 2));
		former_token->cmd_args[*arg_n] = ft_strdup(elem);
		if (former_token->cmd_args[*arg_n] == NULL)
			exit (1);
		former_token->cmd_args[*arg_n + 1] = NULL;
		(*arg_n)++;
		return (arg_n);
	}
	*arg_n = 0;
	if (ft_strcmp(*new_kind, "pipe") == 0)
	{
		former_token->cmd_pipe = 1;
		new_token = new_cmd_token();
		if (new_token == NULL)
			exit (1);
		former_token->next = new_token;
		former_token = new_token;
		return (arg_n);
	}
	if (ft_strncmp(*new_kind, "special", 7) == 0)
		return (arg_n);
	if (ft_strcmp(*new_kind, "command") == 0)
	{
		former_token->cmd = ft_strdup(elem);
		if (former_token->cmd == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "input") == 0)
	{
		former_token->redir_input_name = ft_strdup(elem);
		if (former_token->redir_input_name == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "output") == 0)
	{
		former_token->redir_output_name = ft_strdup(elem);
		if (former_token->redir_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "heredoc") == 0)
	{
		former_token->heredoc_del = ft_strdup(elem);
		if (former_token->heredoc_del == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "append") == 0)
	{
		former_token->append_output_name = ft_strdup(elem);
		if (former_token->append_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	/*
		Los 'inmediate' se producen cuando los 'special' no dejan un espacio detrás,
		sino que van unidos al propio nombre del archivo.
		En esos casos, hay que montar ya la string del archivo, pero saltándonos los 'specials'.
	*/
	if (ft_strcmp(*new_kind, "inmediate_input") == 0)
	{
		former_token->redir_input_name = ft_strdup(elem + 1);
		if (former_token->redir_input_name == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "inmediate_output") == 0)
	{
		former_token->redir_output_name = ft_strdup(elem + 1);
		if (former_token->redir_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "inmediate_heredoc") == 0)
	{
		former_token->heredoc_del = ft_strdup(elem + 2);
		if (former_token->heredoc_del == NULL)
			exit (1);
		return (arg_n);
	}
	if (ft_strcmp(*new_kind, "inmediate_append") == 0)
	{
		former_token->append_output_name = ft_strdup(elem + 2);
		if (former_token->append_output_name == NULL)
			exit (1);
		return (arg_n);
	}
	else
	{
		//En caso de invalid habrá que dar error
		printf("placeholder: error! ... invalid arg");
		exit(1);
	}
	return (arg_n);
}

/*
	Recorremos el array del input y vamos tokenizando en lista enlazada.
	Si es el primer elemento lo guardamos como el "start" de la lista.
	El "former" token lo vamos actualizando cuando hay un nuevo comando,
	y reenviando en cada iteración para que rellenar su contenido.
*/
t_tokens	*tokenize_everything(t_shell shell)
{
	int			i;
	int			arg_n;
	char		*new_kind;
	t_tokens	*former_token;
	t_tokens	*start_token;

	new_kind = NULL;
	arg_n = 0;
	i = 0;
	former_token = new_cmd_token();
	start_token = former_token;
	while (shell.user_input[i])
	{
		tokenize_element(shell.user_input[i], former_token, &arg_n, &new_kind);
		i++;
	}
	return (start_token);
}
