/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/28 14:15:09 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	**command;
	char	**envp;
	char	*pwd;
	char	*path;
	int		exit_status;
}	t_shell;

//Esta struct guarda 1 solo comando con todos sus args y demases.
typedef struct s_tokens
{
	char		*cmd;
	char		**cmd_args;
	int			*cmd_pipe;
//	char		*cmd_env_var;	//$PWD
	t_file		*redir_input;
	t_file		*redir_output;
	char		*heredoc_del;
	t_file		*append_output;
}	t_tokens;

// Struct para los archivos que se usen
typedef struct s_file
{
	char	*file;
	int		fd;
}	t_file;

char	*my_getenv(char *name, char **envp);
char	**array_cpy(char **array);
void	free_shell(t_shell *shell);
void	init_shell(t_shell *shell, char **envp);
int		ft_pwd(t_shell *shell);
int		ft_cd(char **envp);
int		ft_env(t_shell *shell);
int		ft_echo(char **command, char **envp);
int		ft_exit(char ***command, t_shell *shell);
int		ft_export(char **command, t_shell *shell);
int		ft_unset(char **command, t_shell *shell);

#endif
