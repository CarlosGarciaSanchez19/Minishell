/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/04 15:51:37 by dsoriano         ###   ########.fr       */
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

void	execute_tokens(t_tokens *tokens, t_shell *shell) // Necesitamos crear una lista de structs t_tokens
{
	int			(*pipes)[2]; // Si hace falta se declara en el main. Esto es un array de arrays de 2 ints cada uno (pipes).
	int			i;
	int			child_status;
	int			num_pipes;
	pid_t		pid;
	t_tokens	*fst_tkn;
	char		**command_arr;

	 // Esta función es para debuggear, se puede borrar
	/* print_tokens(tokens); */
	num_pipes = tkn_lst_size(tokens) - 1;
	if (num_pipes < 0)
		return ;
	pipes = malloc(sizeof(int [2]) * num_pipes);
	if (!pipes)
		error_pipe(tokens, shell);
	create_pipes(num_pipes, pipes, tokens, shell);
	fst_tkn = tokens;
	i = 0;
	while (tokens)
	{
		// Aquí se ejecutan los comandos
		pid = fork();
		if (pid < 0)
		{
			ft_printf("Error: Fork failed\n");
			exit(1);
		}
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			if (tokens->cmd && !is_built_in(tokens))
				find_command(tokens, shell);
			if (tokens->redir_input_name)
				redirect_input(tokens->redir_input_name);			// Si hay redirección de entrada, la hacemos antes de ejecutar el comando
			else if (tokens->heredoc_del)
				heredoc(tokens, shell, NULL);
			else if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);				// Si no es el primer comando y no hay redireccion de entrada, redirigimos la entrada al pipe anterior
			if (tokens->redir_output_name)
				redirect_output(tokens->redir_output_name); 		// Si hay redirección de salida, la hacemos antes de ejecutar el comando
			else if (tokens->append_output_name)
				append_output(tokens->append_output_name);			// Si hay redirección de salida en modo append, la hacemos antes de ejecutar el comando
			else if (tokens->cmd_pipe && i < num_pipes)
				dup2(pipes[i][1], STDOUT_FILENO);					// Si hay pipe y no es el último comando, redirigimos la salida al pipe
			shell->is_child = 1;
			if (tokens->cmd && !built_in(tokens, shell))
			{
				command_arr = create_command_array(tokens);
				execve(tokens->cmd, command_arr, shell->envp);			// Ejecutamos el comando si no es un built-in
				ft_freearray(command_arr, ft_arraylen(command_arr));		// Liberamos memoria si no se ha ejecutado el comando
				exit(1);
			}
			else
				exit(0);											// Si es un built-in, salimos del proceso hijo
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &child_status, 0);							// En el padre esperamos a todos los procesos hijos y cerramos los pipes que se han usado
			//printf("Child status: %d\n", WEXITSTATUS(child_status));
			shell->exit_status = WEXITSTATUS(child_status);
			close_used_pipe(num_pipes, pipes, i);
			if (WEXITSTATUS(child_status) == 3)
			{
				free_tokens(fst_tkn);
				free(pipes);
				ft_printf("exit\n");
				exit(0);
			}
			else if (WEXITSTATUS(child_status) == 4)
				exit(1);
			if (tokens->cmd)
				built_in(tokens, shell);
		}
		tokens = tokens->next;
		i++;
	}
	free_tokens(fst_tkn);
	free(pipes);
}
