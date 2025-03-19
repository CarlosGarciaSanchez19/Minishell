/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:59:27 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/19 14:01:53 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_str_expansion_regular(char **env_var, char **str,
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

static void	aux_str_expansion_except(char **env_var, char **str,
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
