/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:36:47 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 22:28:16 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_pipe(t_tokens *tokens, t_shell *shell)
{
	write(2, "Error: Pipe could not be created\n", 33);
	free_tokens(tokens);
	free_shell(shell);
	if (shell->is_child)
		exit(4);
	exit(101);
}

void	error_fork(t_tokens *tokens, t_shell *shell)
{
	write(2, "Error: fork could not be created\n", 33);
	free_tokens(tokens);
	free_shell(shell);
	if (shell->is_child)
		exit(5);
	exit(103);
}
