/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/13 15:24:17 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tokens(t_tokens *tokens)
{
	char **args;

	while (tokens != NULL)
	{
		printf("\n-------------\n");
		printf("ESTE TOKEN ES: %p\n", tokens);
		printf("Command: %s\n", tokens->cmd);
		printf("Arguments:\n");
		args = tokens->cmd_args;
		while (args && *args)
		{
			printf("%s\n", *args);
			args++;
		}
		if (tokens->cmd_pipe)
			printf("Pipe: yes\n");
		else
			printf("Pipe: no\n");
		printf("Input redirection: %s\n", tokens->redir_input_name);
		printf("Output redirection: %s\n", tokens->redir_output_name);
		printf("Heredoc delimiter: %s\n", tokens->heredoc_del);
		printf("Append output: %s\n", tokens->append_output_name);
		tokens = tokens->next;
	}
}

void	free_exec_vars(t_tokens *tokens, int (*pipes)[2], int *pids)
{
	if (tokens)
		free_tokens(tokens);
	if (pipes)
		free(pipes);
	if (pids)
		free(pids);
}

void	execute_tokens(t_tokens *tokens, t_shell *shell) // Necesitamos crear una lista de structs t_tokens
{
	int			(*pipes)[2];
	int			i;
	int			*pids;
	int			child_status;
	int			num_pipes;
	pid_t		pid;
	t_tokens	*current_tkn;
	char		**command_arr;

	 // Esta función es para debuggear, se puede borrar
	/* print_tokens(tokens); */
	child_status = 0;
	num_pipes = tkn_lst_size(tokens) - 1;
	if (num_pipes < 0)
		return ;
	pipes = malloc(sizeof(int [2]) * num_pipes);
	if (!pipes)
	{
		free_tokens(tokens);
		free_shell(shell);
		exit(100);
	}
	pids = malloc(sizeof(int) * (num_pipes + 1));
	if (!pids)
	{
		free_exec_vars(tokens, pipes, NULL);
		free_shell(shell);
		exit(100);
	}
	create_pipes(num_pipes, pipes, tokens, shell);
	current_tkn = tokens;
	i = 0;
	while (current_tkn)
	{
		if (current_tkn->cmd && !is_built_in(current_tkn))
			shell->exit_status = find_command(current_tkn, shell);
		// Aquí se ejecutan los comandos
		pid = fork();
		if (pid < 0)
		{
			ft_printf("Error: Fork failed\n");
			free_exec_vars(tokens, pipes, pids);
			exit(1);
		}
		else if (pid == 0)
		{
			shell->is_child = 1;
			signal(SIGINT, SIG_DFL);
			if (current_tkn->redir_input_name)
				redirect_input(current_tkn->redir_input_name);			// Si hay redirección de entrada, la hacemos antes de ejecutar el comando
			else if (current_tkn->heredoc_del)
				heredoc(current_tkn, shell, NULL);
			else if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);				// Si no es el primer comando y no hay redireccion de entrada, redirigimos la entrada al pipe anterior
			if (current_tkn->redir_output_name)
				redirect_output(current_tkn->redir_output_name); 		// Si hay redirección de salida, la hacemos antes de ejecutar el comando
			else if (current_tkn->append_output_name)
				append_output(current_tkn->append_output_name);			// Si hay redirección de salida en modo append, la hacemos antes de ejecutar el comando
			else if (current_tkn->cmd_pipe && i < num_pipes)
				dup2(pipes[i][1], STDOUT_FILENO);					// Si hay pipe y no es el último comando, redirigimos la salida al pipe
			/* close_used_pipe(num_pipes, pipes, i); */
			if (current_tkn->cmd && !is_built_in(current_tkn))
			{
				command_arr = create_command_array(current_tkn);
				execve(current_tkn->cmd, command_arr, shell->envp);			// Ejecutamos el comando si no es un built-in
				ft_freearray(command_arr, ft_arraylen(command_arr));		// Liberamos memoria si no se ha ejecutado el comando
				exit(127);
			}
			else if (current_tkn->cmd && is_built_in(current_tkn) && num_pipes)
				exit(built_in(current_tkn, shell));
			else
				exit(0);
		}
		else
		{
			pids[i] = pid;
			signal(SIGINT, SIG_IGN);
			if (current_tkn->cmd && is_built_in(current_tkn) && !num_pipes)
				shell->exit_status = built_in(current_tkn, shell);
		}
		current_tkn = current_tkn->next;
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < num_pipes + 1)
	{
		if (i == num_pipes)
			waitpid(pids[i], &child_status, 0);
		else
			waitpid(pids[i], NULL, 0);
		i++;
	}
	if ((tokens->cmd && !is_built_in(tokens)) || num_pipes)
		shell->exit_status = WEXITSTATUS(child_status);
	free_exec_vars(tokens, pipes, pids);
	if (WEXITSTATUS(child_status) == 4)
		exit(101);
}
