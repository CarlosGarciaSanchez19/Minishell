/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:17:08 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 12:34:45 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(t_pipes *p, t_tokens *tokens, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < p->num_pipes)
	{
		if (pipe(p->pipes[i]) < 0)
			error_pipe(tokens, shell);
		i++;
	}
}

void	close_used_pipe(t_pipes *p, int i)
{
	if (i > 0)
		close(p->pipes[i - 1][0]);
	if (i < p->num_pipes)
		close(p->pipes[i][1]);
}

void	close_all_pipes(t_pipes	*p)
{
	int	i;

	i = 0;
	while (i < p->num_pipes)
	{
		close(p->pipes[i][0]);
		close(p->pipes[i][1]);
		i++;
	}
}
