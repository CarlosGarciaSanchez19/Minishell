/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/04 15:22:14 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Recorremos el elemento para determinar que tipo de input es.
*/
char	*search_for_kind(char *elem, char *former_kind)
{
	if (elem[0] == '|' && elem[1] == '\0')
		return ("pipe");
	if (elem[0] == '<')
	{
		if (elem[1] == '\0')
			return ("special_input");
		if (elem[1] == '<' && elem[2] == '\0')
			return ("special_heredoc");
	}
	if (elem[0] == '>')
	{
		if (elem[1] == '\0')
			return ("special_output");
		if (elem[1] == '>' && elem[2] == '\0')
			return ("special_append");
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

	token = malloc(sizeof(t_tokens));
	if (token == NULL)
		return (NULL);
	token->next = NULL;
	return (token);
}

/*
	En cada 'elem' sacamos su tipo como string y hacemos cosas distintas en función del tipo
*/
void	tokenize_element(char *elem, t_tokens *former_token, int *arg_n, char *new_kind)
{
	t_tokens	*new_token;

	new_kind = search_for_kind(elem, new_kind);
	if (new_kind == "argument")
	{
		//En caso de argumento, hay que añadirlo al array de argumentos,
		//en la posición siguiente. Duplicando la string que contiene el comando.
		//Y actualizar la posición.
		former_token->cmd_args[*arg_n] = ft_strdup(elem);
		*arg_n++;
		return ;
	}
	*arg_n = 0;
	if (new_kind == "pipe")
	{
		//En caso de pipe, hay que añadirsela al token de cmd previo
		//pero tambien hay que crear un nuevo struct (new)) conectado con el anterior,
		//y luego el nuevo se convierte en former
		former_token->cmd_pipe = 1;
		new_token = new_cmd_token();
		former_token->next = new_token;
		former_token = new_token;
		return ;
	}
	if (new_kind == "special")
		return ;
	if (new_kind == "command")
	{
		former_token->cmd = ft_strdup(elem);
		return ;
	}
	if (new_kind == "input")
	{
		former_token->redir_input_name = ft_strdup(elem);
		return ;
	}
	if (new_kind == "output")
	{
		former_token->redir_output_name = ft_strdup(elem);
		return ;
	}
	if (new_kind == "heredoc")
	{
		former_token->heredoc_del = ft_strdup(elem);
		return ;
	}
	if (new_kind == "append")
	{
		former_token->append_output_name = ft_strdup(elem);
		return ;
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
void	tokenize_everything(t_shell shell)
{
	int			i;
	int			*arg_n;
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
		tokenize_element(shell.user_input[i], &former_token, arg_n, new_kind);
		i++;
	}
}
