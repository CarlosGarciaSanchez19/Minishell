/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:01:36 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 14:53:34 by carlosg2         ###   ########.fr       */
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

static	int	command_found(char *path_bar_cmd, char **cmd)
{
	if (access(path_bar_cmd, F_OK) == 0)
	{
		free(*cmd);
		*cmd = path_bar_cmd;
		return (1);
	}
	return (0);
}

static char	**path_split(char **envp)
{
	char	*path_var;
	char	**null_array;

	path_var = my_getenv("PATH", envp);
	if (path_var)
		return (ft_split(path_var, ':'));
	else
	{
		null_array = (char **)malloc(sizeof(char *));
		*null_array = NULL;
		return (null_array);
	}
}

int	find_command(t_tokens *tkn, t_shell *shell)
{
	char	**paths;
	char	*path_bar;
	char	*path_bar_cmd;
	int		i;

	if (tkn->cmd && access(tkn->cmd, X_OK) == 0)
		return (0);
	paths = path_split(shell->envp);
	if (!paths)
		return (100);
	i = 0;
	while (paths[i])
	{
		path_bar = ft_strjoin(paths[i], "/");
		path_bar_cmd = ft_strjoin(path_bar, tkn->cmd);
		if (!path_bar || !path_bar_cmd)
			return (ft_free_multiarray((void **)paths), 0);
		free(path_bar);
		if (command_found(path_bar_cmd, &(tkn->cmd)))
			return (ft_free_multiarray((void **)paths), 1);
		free(path_bar_cmd);
		i++;
	}
	write(2, "Command '", 9);
	write(2, tkn->cmd, ft_strlen(tkn->cmd));
	write(2, "' not found.\n", 13);
	ft_free_multiarray((void **)paths);
	return (127);
}

char	*path_and_readline(t_shell *shell)
{
	char	*fst_part;
	char	*final_str;
	char	*input;

	fst_part = ft_strjoin(YELLOW, shell->pwd);
	final_str = ft_strjoin(fst_part, BLUE" $> "RESET);
	free(fst_part);
	// Readline se queda escuchando. Pero antes printea la string que le pases como argumento.
	// Nosotros le pasamos el Path/PWD actual con "$>".
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

	tokens = tokenize_everything(*shell);
	execute_tokens(tokens, shell);
	ft_free_multiarray((void **)shell->user_input);
	ft_free_multiarray((void **)shell->orig_input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell 	shell;
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
