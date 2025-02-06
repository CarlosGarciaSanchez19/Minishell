/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/06 14:19:45 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"

# define bool int
# define true 1
# define false 0

typedef struct s_shell
{
	char	**user_input;
	char	**envp;
	char	*pwd;
	char	*path;
	char	*history_file;
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
	bool			cmd_pipe;
	char			*redir_input_name;
	char			*redir_output_name;
	char			*heredoc_del;
	char			*append_output_name;
	struct s_tokens	*next;
}	t_tokens;

char		*my_getenv(char *name, char **envp);
char		**array_cpy(char **array);
void		free_shell(t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
int			is_built_in(t_tokens *tkn, t_shell *shell);
int			ft_pwd(t_shell *shell);
int			ft_cd(char **envp);
int			ft_env(t_shell *shell);
int			ft_echo(char **command, char **envp);
int			ft_exit(char ***command, t_shell *shell);
int			ft_export(char **cmd_args, t_shell *shell);
int			ft_unset(char **cmd_args, t_shell *shell);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
t_tokens	*tokenize_everything(t_shell shell);
int			find_command(t_tokens *tkn, t_shell *shell);
void		execute_tokens(t_tokens *tokens, t_shell *shell);

#endif
