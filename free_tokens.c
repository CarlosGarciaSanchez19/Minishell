/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:34:29 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/24 20:36:48 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*current_tkn;
	t_tokens	*prev_tkn;

	if (tokens == NULL)
		return ;
	prev_tkn = NULL;
	current_tkn = tokens;
	while (current_tkn)
	{
		if (current_tkn->cmd)
			free(current_tkn->cmd);
		if (current_tkn->cmd_args)
			ft_free_multiarray((void **)current_tkn->cmd_args);
		if (current_tkn->redir_input_name)
			free(current_tkn->redir_input_name);
		if (current_tkn->redir_output_name)
			free(current_tkn->redir_output_name);
		if (current_tkn->heredoc_del)
			free(current_tkn->heredoc_del);
		if (current_tkn->append_output_name)
			free(current_tkn->append_output_name);
		prev_tkn = current_tkn;
		current_tkn = current_tkn->next;
		free(prev_tkn);
	}
}
