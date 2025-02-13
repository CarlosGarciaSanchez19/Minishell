/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/13 12:02:53 by carlosg2         ###   ########.fr       */
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

char	**create_command_array(t_tokens *tokens)
{
	char	**command;
	int		i;

	if (!tokens->cmd_args)
		return (NULL);
	i = 0;
	command = malloc(sizeof(char *) * (ft_arraylen(tokens->cmd_args)+ 2));
	if (!command)
	{
		ft_printf("Error: Command array could not be created\n");
		exit(1);
	}
	command[i] = tokens->cmd;
	i++;
	while (tokens->cmd_args[i - 1])
	{
		command[i] = tokens->cmd_args[i - 1];
		i++;
	}
	command[i] = NULL;
	return (command);
}

void	execute_tokens(t_tokens *tokens, t_shell *shell) // Necesitamos crear una lista de structs t_tokens
{
	int		(*pipes)[2]; // Si hace falta se declara en el main. Esto es un array de arrays de 2 ints cada uno (pipes).
	int		i;
	int		child_status;
	int		num_pipes;
	pid_t	pid;
	char	**command;

	 // Esta función es para debuggear, se puede borrar
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
		print_tokens(tokens);
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
			if (!built_in(tokens, shell) && find_command(tokens, shell))
			{
				command = create_command_array(tokens);
				execve(tokens->cmd, command, shell->envp);	// Ejecutamos el comando si no es un built-in
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
			built_in(tokens, shell);
			if (WEXITSTATUS(child_status) == 2)
			{
				ft_printf("exit\n");
				exit(0);
			}
		}
		tokens = tokens->next;
		i++;
	}
}
