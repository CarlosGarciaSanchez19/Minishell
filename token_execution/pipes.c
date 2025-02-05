/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/05 13:35:23 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	pipes(t_tokens *tokens, t_shell *shell) // Necesitamos crear una lista de structs t_tokens
{
	int		(*pipes)[2]; // Si hace falta se declara en el main. Esto es un array de arrays de 2 ints cada uno (pipes).
	int		i;
	int		num_pipes;
	pid_t	pid;

	pipes = malloc(sizeof(int [2]) * num_pipes);
	if (!pipes)
	{
		ft_printf("Error: Pipes could not be created\n");
		exit(1);
	}
	num_pipes = ft_lstsize(tokens) - 1;
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
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (tokens->redir_input_name)
				redirect_input(tokens->redir_input_name);
			if (tokens->redir_output_name)
				redirect_output(tokens->redir_output_name);
			else if (tokens->cmd_pipe && i < num_pipes)
				dup2(pipes[i][1], STDOUT_FILENO);
			if (!is_built_in(tokens->cmd_args, shell))
			{
				execve(tokens->cmd, tokens->cmd_args, shell->envp);
				exit(1);
			}
			else
				_exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close_used_pipe(num_pipes, pipes, i);
		}
		tokens = tokens->next;
		i++;
	}
}
