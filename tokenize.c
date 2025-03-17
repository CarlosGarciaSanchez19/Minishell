/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/17 18:16:29 by dsoriano         ###   ########.fr       */
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

void	str_expansion(char **str, int prev_len, t_shell shell)
{
	char	*env_var;
	int		len_env;

	env_var = NULL;
	if (ft_strcmp(*str, "$") == 0)
		;
	else if (ft_strncmp(*str, "$$", 2) == 0)
	{
		env_var = ft_itoa(shell.pid);
		len_env = ft_strlen(env_var);
		free(*str);
		*str = ft_strdup(env_var);
	}
	else if (ft_strncmp(*str, "$?", 2) == 0)
	{
		env_var = ft_itoa(shell.exit_status);
		len_env = ft_strlen(env_var);
		free(*str);
		*str = ft_strdup(env_var);
	}
	else
	{
		env_var = my_getenv(*str + 1, shell.envp);
		if (env_var)
		{
			env_var = ft_strdup(env_var);
			len_env = ft_strlen(env_var);
			free(*str);
			*str = ft_strdup(env_var);
		}
		else
		{
			*str = ft_realloc(*str, prev_len, 1);
			(*str)[0] = '\0';
		}
	}
	if (env_var)
		free(env_var);
}

/*
	Esta función recorre desde donde se encuenra el $ hasta donde se encuentra un no ALNUM.
	Luego actualiza la i de fuera a esa nueva posición, y devuelve la string intermedia.
*/
char	*find_expand(char *str, int *n)
{
	int	i;

	i = 1;
	if (str[1] == '$' || str[1] == '?')
		i++;
	else
	{
		while (str[i] && (isalnum(str[i])))
			i++;
	}
	*n = *n + i;
	return (ft_strndup(str, i));
}

void	expand_env_vars(char **input, int pos, t_shell shell)
{
	int		i;
	int		len_input;

	char	*temp_str;
	char	*big_str;
	char	*temp_big_str;
	int		prev_len;
	int		post_len;
	int		var_len;
	
	var_len = 0;
	big_str = NULL;

	len_input = ft_strlen(input[pos]);
	i = 0;
	while (input[pos] && input[pos][i])
	{
		if (input[pos][i] == '$')
		{
			//LA PRIMERA VEZ SETEAMOS BIG_STR COMO LA STRING HASTA EL $
			if (!big_str)
				big_str = ft_substr(input[pos], 0, i);
			//RECORRE HASTA ENCONTRAR NULL O NO ALFANUM
			//LO METE EN UNA TEMP_STRING
			temp_str = find_expand(input[pos] + i , &i);
			//len_prev_temp
			prev_len = ft_strlen(temp_str);
			//ESA TEMP_STRING LA MANDAMOS A LA STR_EXPANSION
			str_expansion(&temp_str, prev_len, shell);
			//EL RESULTADO DE LA EXPANSION ACTUALIZA LA TEMP_STRING QUE LE HEMOS MANDADO
			//len_post_temp
			post_len = ft_strlen(temp_str);
			//BIG_STR ES LO QUE YA HUBIERA EN ELLA + TEMP_STRING + INPUTPOS DESDE I
			temp_big_str = ft_substr(big_str, 0, (i + var_len - prev_len));
			var_len = var_len + (post_len - prev_len);
			free(big_str);
			big_str = ft_strjoin(temp_big_str, temp_str);
			free(temp_str);
			free(temp_big_str);
			temp_big_str = ft_strjoin(big_str, input[pos] + i);
			free(big_str);
			big_str = temp_big_str;
		}
		else
			i++;
	}
	//AL FINAL DEL BUCLE HAREMOS QUE FINAL_STRING SUSTITUYA INPUT[POS]
	if (big_str)
	{
		free(input[pos]);
		input[pos] = big_str;
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

static int	check_special_valid(t_tokens *start_token)
{
	t_tokens *current_token;

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
			write(2, "Error: Quotes need to be closed\n", 32);
			return (free_tokens(start_token), NULL);
		}
		if (new_kind && ft_strcmp(new_kind, "special_heredoc") == 0)
			former_token->del_pos = i;
		else if (!ft_strissimplequote(shell.orig_input[i]))
			expand_env_vars(shell.user_input, i, shell);
		if (shell.user_input[i] && shell.user_input[i][0])
			tokenize_element(shell.user_input[i], &former_token, &arg_n, &new_kind);
		i++;
	}
	if (!check_special_valid(start_token))
		return (free_tokens(start_token), NULL);
	return (start_token);
}


/* 	if (ft_strcmp(input[pos] + i, "$") == 0)
		;
	else if (ft_strcmp(input[pos] + i, "$$") == 0)
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
		free(env_var); */
