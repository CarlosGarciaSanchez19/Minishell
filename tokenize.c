/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/07 15:05:33 by dsoriano         ###   ########.fr       */
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
			exit(1);
		(*former_token)->cmd_args[*arg_n + 1] = NULL;
		(*arg_n)++;
		return (arg_n);
	}
	*arg_n = 0;
	return (tokenize_element_aux0(elem, former_token, arg_n, new_kind));
}

void	expand_env_vars(char **input, int pos, t_shell shell)
{
	int		i;
	int		len_input;
	int		len_env;
	char	*env_var;

	len_input = ft_strlen(input[pos]);
	i = 0;
	while (input[pos][i])
	{
		if (input[pos][i] == '$')
		{
			if (ft_strcmp(input[pos] + i, "$$") == 0)
			{
				env_var = ft_itoa(shell.pid);
				len_env = ft_strlen(env_var);
				input[pos] = ft_realloc(input[pos], len_input, (i + len_env + 1));
				ft_memcpy(input[pos] + i, env_var, len_env + 1);
			}
			else if (ft_strcmp(input[pos] + i, "$?") == 0)
			{
				env_var = ft_itoa(shell.exit_status);
				len_env = ft_strlen(env_var);
				input[pos] = ft_realloc(input[pos], len_input, (i + len_env + 1));
				ft_memcpy(input[pos] + i, env_var, len_env + 1);
			}
			else
			{
				env_var = my_getenv(input[pos] + i + 1, shell.envp);
				if (env_var)
				{
					env_var = ft_strdup(env_var);
					len_env = ft_strlen(env_var);
					input[pos] = ft_realloc(input[pos], len_input, (i + len_env + 1));
					ft_memcpy(input[pos] + i, env_var, len_env + 1);
				}
				else
				{
					ft_realloc(input[pos], len_input, 1);
					input[pos][0] = '\0';
				}
			}
			if (env_var)
				free(env_var);
		}
		i++;
	}
}

static int	count_quotes(char *str)
{
	int	i;
	int	count;
	int	quote1;
	int	quote2;

	i = 0;
	count = 0;
	quote1 = 0;
	quote2 = 0;
	while (str && str[i])
	{
		if (in_quot(str[i], &quote1, &quote2) == 1)
			count++;
		i++;
	}
	return (count);
}

int	clean_quotes(char **str)
{
	int		i;
	int		j;
	int 	quote1;
	int		quote2;
	char	*new_str;

	i = 0;
	j = 0;
	quote1 = 0;
	quote2 = 0;
	if (!count_quotes(*str))
		return (1);
	new_str = malloc(ft_strlen(*str) - count_quotes(*str) + 1);	
	while (*str && (*str)[i])
	{
		if (in_quot((*str)[i], &quote1, &quote2) == 0)
		{
			new_str[j] = (*str)[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	if ((quote1 == 1 || quote2 == 1))
		return (free(new_str), 0);
	free(*str);
	*str = new_str;
	return (1);
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
		if (clean_quotes(&(shell.user_input[i])) == 0)
		{
			ft_printf("Error: Quotes need to be closed\n");
			return (free_tokens(start_token), NULL);
		}
		expand_env_vars(shell.user_input, i, shell);
		if (shell.user_input[i] && shell.user_input[i][0])
			tokenize_element(shell.user_input[i], &former_token, &arg_n, &new_kind);
		i++;
		if (new_kind && ft_strcmp(new_kind, "special_heredoc") == 0)
			former_token->del_pos = i;
	}
	return (start_token);
}
