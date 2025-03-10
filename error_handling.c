/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:33:38 by dsoriano          #+#    #+#             */
/*   Updated: 2025/03/10 17:03:08 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char **string, t_shell *shell)
{
	(void)shell;
	if (!(*string))
	{
		free(string);
		write(2, "Allocation error\n", 17);
		return (100);
	}
	return (1);
}

int	error_file(char *string, char *arg, t_shell *shell)
{
	(void)shell;
	write(2, "cd: ", 4);
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n", 28);
	if (string)
		free(string);
	return (1);
}

int	error_option(char arg, t_shell *shell)
{
	(void)shell;
	write(2, "cd: ", 4);
	write(2, &arg, 1);
	write(2, ": invalid option\n", 17);
	return (2);
}

void	error_pipe(t_tokens *tokens, t_shell *shell)
{
	write(2, "Error: Pipe could not be created\n", 33);
	free_tokens(tokens);
	free_shell(shell);
	if (shell->is_child)
		exit(4);
	exit(101);
}
