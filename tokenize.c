/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/18 15:48:54 by carlosg2         ###   ########.fr       */
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

void	aux_str_expansion_regular(char **env_var, char **str,
	int *len_env, int prev_len)
{
	if (*env_var)
	{
		*env_var = ft_strdup(*env_var);
		*len_env = ft_strlen(*env_var);
		free(*str);
		*str = ft_strdup(*env_var);
	}
	else
	{
		*str = ft_realloc(*str, prev_len, 1);
		(*str)[0] = '\0';
	}
}

void	aux_str_expansion_except(char **env_var, char **str,
	int *len_env, int n)
{
	*env_var = ft_itoa(n);
	*len_env = ft_strlen(*env_var);
	free(*str);
	*str = ft_strdup(*env_var);
}


void	str_expansion(char **str, int prev_len, t_shell shell)
{
	char	*env_var;
	int		len_env;

	env_var = NULL;
	if (ft_strcmp(*str, "$") == 0)
		;
	else if (ft_strncmp(*str, "$$", 2) == 0)
		aux_str_expansion_except(&env_var, str, &len_env, shell.pid);
	else if (ft_strncmp(*str, "$?", 2) == 0)
		aux_str_expansion_except(&env_var, str, &len_env, shell.exit_status);
	else
	{
		env_var = my_getenv(*str + 1, shell.envp);
		aux_str_expansion_regular(&env_var, str, &len_env, prev_len);
	}
	if (env_var)
		free(env_var);
}

/*
	Esta función recorre desde donde se encuentra el $,
	hasta donde se encuentra un no ALNUM.
	Luego actualiza la i de fuera a esa nueva posición,
	y devuelve la string intermedia.
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

/*
	Función para ahorrar líneas que libera la primera string,
	y mete dentro de ella la unión de la segunda y tercera string,
	y libera la cuarta string también.
*/
void	aux_free_join_free(char **first_str, char *second_str, char *third_str, char **fourth_str)
{
	free(*first_str);
	*first_str = ft_strjoin(second_str, third_str);
	free(*fourth_str);
}

/*
	Auxiliar que setea vars para ahorrar líneas.
*/
void	aux_set_vars(char **big_str, int (*lens)[2], int *i)
{
	*big_str = NULL;
	(*lens)[1] = 0;
	*i = 0;
}

/*
	Auxiliar que cambia input por big_str,
	solo si se ha llegado a hacer el bucle que genera big_str.
*/
void	aux_change_input(char **big_str, char **input)
{
	if (*big_str)
	{
		free(*input);
		*input = *big_str;
	}
}

/*
	Auxiliar que inicializa big_str como el inicio de la frase,
	pero solo la primera vez que se entra en el bucle.
*/
void	aux_start_big_str(char **big_str, char *input, int i)
{
	if (!(*big_str))
		*big_str = ft_substr(input, 0, i);
}

/*
	La primera vez que entra en el bucle seteamos big_str (la string hasta $).
	Recorremos hasta NULL o no alfanum y lo metemos en temp_str.
	Temp_str la expandimos y es actualizada ahí dentro.
	Al final, big_str es: big_str + temp_str + lo que haya tras la I.
	Al acabar el bucle, hacemos que la big_str sustituya al input[pos],
	pero solo en caso de que que se haya pasado por el bucle.
*/
void	expand_env_vars(char **input, t_shell shell)
{
	char	*temp_str;
	char	*big_str;
	char	*temp_big_str;
	int		i;
	int		lens[2];
	
	aux_set_vars(&big_str, &lens, &i);
	while (*input && (*input)[i])
	{
		if ((*input)[i] == '$')
		{
			aux_start_big_str(&big_str, *input, i);
			temp_str = find_expand(*input + i , &i);
			lens[0] = ft_strlen(temp_str);
			str_expansion(&temp_str, lens[0], shell);
			temp_big_str = ft_substr(big_str, 0, (i + lens[1] - lens[0]));
			lens[1] = lens[1] + (ft_strlen(temp_str) - lens[0]);			
			aux_free_join_free(&big_str, temp_big_str, temp_str, &temp_str);
			aux_free_join_free(&temp_big_str, big_str, *input + i, &big_str);
			big_str = temp_big_str;
		}
		else
			i++;
	}
	aux_change_input(&big_str, input);
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

/*
	Auxiliar para setear las variables del clean quotes.
*/
void	aux_clean_quotes(int *i, int *j, int *quote1, int *quote2)
{
	*i = 0;
	*j = 0;
	*quote1 = 0;
	*quote2 = 0;
}

int	clean_quotes(char **str)
{
	int		i;
	int		j;
	int 	quote1;
	int		quote2;
	char	*new_str;

	aux_clean_quotes(&i, &j, &quote1, &quote2);
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

int	aux_initvars_tokenize_everything(char **new_kind, int *arg_n,
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
t_tokens	*tokenize_everything(t_shell shell)
{
	int			i;
	int			arg_n;
	char		*new_kind;
	t_tokens	*former_token;
	t_tokens	*start_token;

	i = aux_initvars_tokenize_everything(&new_kind, &arg_n, &former_token, &start_token);
	while (shell.user_input[i])
	{
		if (clean_quotes(&(shell.user_input[i])) == 0)
		{
			write(2, "Error: Quotes need to be closed\n", 32);
			return (free_tokens(start_token), NULL);
		}
		if (new_kind && ft_strcmp(new_kind, "special_heredoc") == 0)
			former_token->del_pos = i;
		else if (!ft_strhassimplequote(shell.orig_input[i]))
			expand_env_vars(&(shell.user_input[i]), shell);
		if (shell.user_input[i] && shell.user_input[i][0])
			tokenize_element(shell.user_input[i], &former_token, &arg_n, &new_kind);
		i++;
	}
	if (!check_special_valid(start_token))
		return (free_tokens(start_token), NULL);
	return (start_token);
}
