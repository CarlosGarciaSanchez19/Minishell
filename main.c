/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:01:36 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/08 13:30:29 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*input;

	if (argc != 1)
		return (1);
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		// Read the command
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		// Parse the command
		// Execute the command
		free(input);
	}
	return (0);
}
