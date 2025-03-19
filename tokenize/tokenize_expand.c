/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:55:43 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/19 15:01:37 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Auxiliar que cambia input por big_str,
	solo si se ha llegado a hacer el bucle que genera big_str.
*/
static void	aux_change_input(char **big_str, char **input)
{
	if (*big_str)
	{
		free(*input);
		*input = *big_str;
	}
}

/*
	Función para ahorrar líneas que libera la primera string,
	y mete dentro de ella la unión de la segunda y tercera string,
	y libera la cuarta string también.
*/
static void	aux_free_join_free(char **first_str, char *second_str,
		char *third_str, char **fourth_str)
{
	free(*first_str);
	*first_str = ft_strjoin(second_str, third_str);
	free(*fourth_str);
}

/*
	Auxiliar que inicializa big_str como el inicio de la frase,
	pero solo la primera vez que se entra en el bucle.
*/
static void	aux_start_big_str(char **big_str, char *input, int i)
{
	if (!(*big_str))
		*big_str = ft_substr(input, 0, i);
}

/*
	Auxiliar que setea vars para ahorrar líneas.
*/
static void	aux_set_vars(char **big_str, int (*lens)[2], int *i)
{
	*big_str = NULL;
	(*lens)[1] = 0;
	*i = 0;
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
			temp_str = find_expand(*input + i, &i);
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
