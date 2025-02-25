/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:17:08 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/25 18:39:46 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(
	int n_pipes,
	int pipes[n_pipes][2],
	t_tokens *tokens,
	t_shell *shell
)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipe(pipes[i]) < 0)
			error_pipe(tokens, shell);
		i++;
	}
}

void	close_used_pipe(int n_pipes, int pipes[n_pipes][2], int i)
{
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < n_pipes)
		close(pipes[i][1]);
}
