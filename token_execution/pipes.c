/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/06 14:42:24 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tkn_lst_size(t_tokens *tkn)
{
	int		i;

	i = 0;
	while (tkn)
	{
		i++;
		tkn = tkn->next;
	}
	return (i);
}

void	create_pipes(int n_pipes,int pipes[n_pipes][2])
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipe(pipes[i]) < 0)
		{
			ft_printf("Error: Pipe could not be created\n");
			exit(1);
		}
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

void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: File %s could not be opened\n", file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(char *file)
{
	int	fd;

	fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printf("Error: File %s could not be opened\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	print_tokens(t_tokens *tokens)
{
	char **args;
	while (tokens)
	{
		ft_printf("Command: %s\n", tokens->cmd);
		ft_printf("Arguments:\n");
		args = tokens->cmd_args;
		while (args)
		{
			ft_printf("%s\n", *args);
			args++;
		}
		if (tokens->cmd_pipe)
			ft_printf("Pipe: yes\n");
		else
			ft_printf("Pipe: no\n");
		ft_printf("Input redirection: %s\n", tokens->redir_input_name);
		ft_printf("Output redirection: %s\n", tokens->redir_output_name);
		ft_printf("Heredoc delimiter: %s\n", tokens->heredoc_del);
		ft_printf("Append output: %s\n", tokens->append_output_name);
		tokens = tokens->next;
	}
}

void	execute_tokens(t_tokens *tokens, t_shell *shell) // Necesitamos crear una lista de structs t_tokens
{
	int		(*pipes)[2]; // Si hace falta se declara en el main. Esto es un array de arrays de 2 ints cada uno (pipes).
	int		i;
	int		child_status;
	int		num_pipes;
	pid_t	pid;

	print_tokens(tokens); // Esta función es para debuggear, se puede borrar
	num_pipes = tkn_lst_size(tokens) - 1;
	pipes = malloc(sizeof(int [2]) * num_pipes);
	if (!pipes)
	{
		ft_printf("Error: Pipes could not be created\n");
		exit(1);
	}
	create_pipes(num_pipes, pipes);
	i = 0;
	while (i <= num_pipes)
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
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);				// Si no es el primer comando, redirigimos la entrada al pipe anterior
			if (tokens->redir_input_name)
				redirect_input(tokens->redir_input_name);			// Si hay redirección de entrada, la hacemos antes de ejecutar el comando
			if (tokens->redir_output_name)
				redirect_output(tokens->redir_output_name); 		// Si hay redirección de salida, la hacemos antes de ejecutar el comando
			else if (tokens->cmd_pipe && i < num_pipes)
				dup2(pipes[i][1], STDOUT_FILENO);					// Si hay pipe y no es el último comando, redirigimos la salida al pipe
			if (!is_built_in(tokens, shell) && find_command(tokens, shell))
			{
				execve(tokens->cmd, tokens->cmd_args, shell->envp);	// Ejecutamos el comando si no es un built-in
				exit(1);
			}
			else if (ft_strcmp(tokens->cmd, "exit") == 0)
				exit(2);
			else
				exit(0);											// Si es un built-in, salimos del proceso hijo
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &child_status, 0);									// En el padre esperamos a todos los procesos hijos y cerramos los pipes que se han usado
			/* ft_printf("Child status: %d\n", WEXITSTATUS(child_status)); */
			close_used_pipe(num_pipes, pipes, i);
			signal(SIGINT, sigint_handler);
			if (WEXITSTATUS(child_status) == 2)
				exit(0);
		}
		tokens = tokens->next;
		i++;
	}
}
