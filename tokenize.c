/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/18 17:34:20 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	En cada 'elem' sacamos su tipo como string,
	y hacemos cosas distintas en función del tipo.
*/
static int	*tokenize_element(char *elem, t_tokens **former_token,
	int *arg_n, char **new_kind)
{
	*new_kind = search_for_kind(elem, *new_kind);
/* 	printf("elem: %s\n", elem);
	printf("new_kind: %s\n", *new_kind); */
	if (ft_strcmp(*new_kind, "argument") == 0)
	{
//		printf("TOKEN PREREALLOC ES: %p\n", (*former_token));
		if (*arg_n == 0)
			(*former_token)->cmd_args = malloc(sizeof(char *) * (*arg_n + 2));
		else
			(*former_token)->cmd_args = ft_realloc((*former_token)->cmd_args,
					sizeof(char *) * (*arg_n + 2));
		(*former_token)->cmd_args[*arg_n] = ft_strdup(elem);
		if ((*former_token)->cmd_args[*arg_n] == NULL)
			exit(1);
//		printf("TOKEN POSTREALLOC ES: %p\n", (*former_token));
		(*former_token)->cmd_args[*arg_n + 1] = NULL;
		(*arg_n)++;
		return (arg_n);
	}
	*arg_n = 0;
	return (tokenize_element_aux0(elem, former_token, arg_n, new_kind));
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
		tokenize_element(shell.user_input[i], &former_token, &arg_n, &new_kind);
		i++;
		printf("new_kind: %s\n", new_kind);
	}
	//comprobar parseo si el formato era valido porque por ejemplo < y >
	//no pueden ir al final (tiene que dar un error concreto)
	return (start_token);
}
