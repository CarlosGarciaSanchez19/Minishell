/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:52:27 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/19 15:01:41 by dsoriano         ###   ########.fr       */
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

int	clean_quotes(char **str)
{
	int		i;
	int		j;
	int		quote1;
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
