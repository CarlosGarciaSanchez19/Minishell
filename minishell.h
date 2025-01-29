/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/29 17:12:23 by carlosg2         ###   ########.fr       */
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
# include <signal.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	**user_input;
	char	**envp;
	char	*pwd;
	char	*path;
	int		exit_status;
}	t_shell;

// Struct para los archivos que se usen
typedef struct s_file
{
	char	*file;
	int		fd;
}	t_file;

//Esta struct guarda 1 solo comando con todos sus args y demases.
typedef struct s_tokens
{
	char			*cmd;
	char			**cmd_args;
	int				*cmd_pipe;
//	char			*cmd_env_var;	//$PWD
	t_file			*redir_input;
	t_file			*redir_output;
	char			*heredoc_del;
	t_file			*append_output;
	struct s_tokens	*next;
}	t_tokens;

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
void	sigint_handler(int signum);
void	sigquit_handler(int signum);

#endif
