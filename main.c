/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:01:36 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/19 15:39:13 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *name, char **envp)
{
	int		name_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	while (*envp)
	{
		if (ft_strncmp(*envp, name, name_len) == 0 && (*envp)[name_len] == '=')
			return (*envp + name_len + 1);
		envp++;
	}
	return (NULL);
}

char	*path_and_readline(t_shell *shell)
{
	char	*fst_part;
	char	*final_str;
	char	*input;

	fst_part = ft_strjoin(YELLOW, shell->pwd);
	final_str = ft_strjoin(fst_part, BLUE" $> "RESET);
	free(fst_part);
	input = readline(final_str);
	free(final_str);
	return (input);
}

void	manage_input(char *input, t_shell *shell)
{
	if (!input)
	{
		free_shell(shell);
		ft_printf("exit\n");
		exit(0);
	}
	if (*input)
	{
		add_history(input);
		write_history(NULL);
	}
}

void	tokenize_and_execute(t_shell *shell)
{
	t_tokens	*tokens;

	tokens = tokenize_everything(shell);
	if (!tokens)
	{
		ft_free_multiarray((void **)shell->user_input);
		ft_free_multiarray((void **)shell->orig_input);
		return ;
	}
	execute_tokens(tokens, shell);
	ft_free_multiarray((void **)shell->user_input);
	ft_free_multiarray((void **)shell->orig_input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*input;

	if (argc != 1)
		return (1);
	(void)argv;
	init_shell(&shell, envp);
	read_history(NULL);
	stifle_history(100);
	rl_catch_signals = 0;
	rl_attempted_completion_function = minishell_completion;
	while (1)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = path_and_readline(&shell);
		manage_input(input, &shell);
		shell.user_input = ft_splitquot(input, ' ');
		shell.orig_input = array_cpy(shell.user_input);
		free(input);
		tokenize_and_execute(&shell);
	}
	free_shell(&shell);
	return (0);
}
