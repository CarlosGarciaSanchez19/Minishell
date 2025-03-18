/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/18 13:21:27 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_exec_vars(t_tokens *tokens, int (*pipes)[2])
{
	if (tokens)
		free_tokens(tokens);
	if (pipes)
		free(pipes);
}

void	redirections(t_tokens *curr_tkn, t_shell *shell, t_pipes *p, int i)
{
	if (curr_tkn->redir_input_name)
		redirect_input(curr_tkn->redir_input_name, curr_tkn);
	else if (curr_tkn->heredoc_del)
		heredoc(curr_tkn, shell, NULL);
	else if (i > 0)
		dup2((p->pipes)[i - 1][0], STDIN_FILENO);
	if (curr_tkn->redir_output_name)
		redirect_output(curr_tkn->redir_output_name, curr_tkn);
	else if (curr_tkn->append_output_name)
		append_output(curr_tkn->append_output_name, curr_tkn);
	else if (curr_tkn->cmd_pipe && i < p->num_pipes)
		dup2((p->pipes)[i][1], STDOUT_FILENO);
}

void	command_child_exec(t_tokens *curr_tkn, t_pipes *p, t_shell *shell)
{
	char	**command_array;

	if (curr_tkn->cmd && !is_built_in(curr_tkn))
	{
		command_array = create_command_array(curr_tkn);
		execve(curr_tkn->cmd, command_array, shell->envp);
		ft_free_multiarray((void **)command_array);
		exit(127);
	}
	else if (curr_tkn->cmd && is_built_in(curr_tkn) && p->num_pipes)
		exit(built_in(curr_tkn, shell));
	else
		exit(0);
}

pid_t	fork_redir_and_execute(t_tokens *curr_tkn, t_shell *shell, t_pipes *p, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		shell->is_child = 1;
		signal(SIGINT, SIG_DFL);
		redirections(curr_tkn, shell, p, i);
		close_all_pipes(p);
		command_child_exec(curr_tkn, p, shell);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		if (curr_tkn->cmd && is_built_in(curr_tkn) && !p->num_pipes)
			shell->exit_status = built_in(curr_tkn, shell);
		close_used_pipe(p, i);
	}
	return (pid);
}

void	init_exec_vars_and_pipe_creat(int *chld_st, t_tokens *tkns, t_pipes *p, t_shell *shell)
{
	*chld_st = 0;
	p->num_pipes = tkn_lst_size(tkns) - 1;
	if (p->num_pipes < 0)
		return ;
	p->pipes = malloc(sizeof(int [2]) * p->num_pipes);
	if (!p->pipes)
	{
		free_tokens(tkns);
		free_shell(shell);
		exit(100);
	}
	create_pipes(p, tkns, shell);
}

void	execute_tokens(t_tokens *tokens, t_shell *shell)
{
	t_pipes		p;
	int			i;
	int			child_status;
	pid_t		pid;
	t_tokens	*current_tkn;

	/* print_tokens(tokens); */
	init_exec_vars_and_pipe_creat(&child_status, tokens, &p, shell);
	current_tkn = tokens;
	i = 0;
	while (current_tkn)
	{
		if (current_tkn->cmd && !is_built_in(current_tkn))
			shell->exit_status = find_command(current_tkn, shell);
		pid = fork_redir_and_execute(current_tkn, shell, &p, i);
		if (pid < 0)
		{
			free_exec_vars(tokens, p.pipes);
			free_shell(shell);
			exit(1);
		}
		current_tkn = current_tkn->next;
		i++;
	}
	waitpid(pid, &child_status, 0);
	while (wait(NULL) > 0)
		;
	if ((tokens->cmd && !is_built_in(tokens)) || p.num_pipes)
		shell->exit_status = WEXITSTATUS(child_status);
	free_exec_vars(tokens, p.pipes);
	if (WEXITSTATUS(child_status) == 4)
		exit(101);
}

/* void	print_tokens(t_tokens *tokens)
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
} */
