/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:52:27 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/20 13:44:44 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
static void	aux_clean_quotes(int *i, int *j, int *quote1, int *quote2)
{
	*i = 0;
	*j = 0;
	*quote1 = 0;
	*quote2 = 0;
}

static int	is_emptyquote(char *str)
{
	int	i;
	int	num_quotes;

	
	i = 0;
	while (str && str[i])
	{
		if (!ft_isquote(str[i]))
			return (0);
		i++;
	}
	num_quotes = count_quotes(str);
	if (num_quotes % 2 == 0)
		return (1);
	else
		return (0);
}

int	clean_quotes(char **str)
{
	int		i;
	int		j;
	int		quote1;
	int		quote2;
	char	*new_str;

	aux_clean_quotes(&i, &j, &quote1, &quote2);
	if (is_emptyquote(*str) || !count_quotes(*str))
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

int	check_quotes(t_tokens *start_token, int i, t_shell *shell)
{
	if (clean_quotes(&(shell->user_input[i])) == 0)
	{
		write(2, "Error: Quotes need to be closed\n", 32);
		shell->exit_status = 102;
		return (free_tokens(start_token), 102);
	}
	return (0);
}
