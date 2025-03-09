/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/10 00:04:29 by carlosg2         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/stat.h>
# include "libft/libft.h"

# define YELLOW "\001\033[1;38;5;220m\002" 
# define BLUE "\001\033[1;38;5;51m\002"
# define RESET "\001\033[0m\002"

typedef struct s_shell
{
	char	**user_input;
	char	**orig_input;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
	char	*path;
	char	*home;
	int		pid;
	int		exit_status;
	int		is_child;
}	t_shell;

// Struct para los archivos que se usen
typedef struct s_heredoc
{
	char	*file;
	int		fd;
}	t_file;

//Esta struct guarda 1 solo comando con todos sus args y demases.
typedef struct s_tokens
{
	char			*cmd;
	char			**cmd_args;
	int				cmd_pipe;
	char			*redir_input_name;
	char			*redir_output_name;
	char			*heredoc_del;
	int				del_pos;
	char			*append_output_name;
	int				special;
	struct s_tokens	*next;
}	t_tokens;

void		free_shell(t_shell *shell);
void		init_shell(t_shell *shell, char **envp);
void		create_pipes(
				int n_pipes,
				int pipes[n_pipes][2],
				t_tokens *tokens,
				t_shell *shell
				);
void		close_used_pipe(int n_pipes, int pipes[n_pipes][2], int i);
void		redirect_input(char *file);
void		redirect_output(char *file);
void		append_output(char *file);
void		heredoc(t_tokens *tokens, t_shell *shell, char *str);
void		execute_tokens(t_tokens *tokens, t_shell *shell);
void		sigint_handler(int signum);
void		free_tokens(t_tokens *tokens);
void		error_pipe(t_tokens *tokens, t_shell *shell);
void		clean_bars(char *str);
void		bubble_sort(char **arr);
void		expand_env_vars(char **input, int pos, t_shell shell);
int			check_string(char **string, t_shell *shell);
int			error_file(char *string, char *arg, t_shell *shell);
int			error_option(char arg, t_shell *shell);
int			tkn_lst_size(t_tokens *tkn);
int			built_in(t_tokens *tkn, t_shell *shell);
int			is_built_in(t_tokens *tkn);
int			ft_pwd(t_shell *shell);
int			ft_cd(t_tokens token, t_shell *shell);
int			change_pwd(t_shell *shell, char *new_pwd);
int			cd_route(t_tokens token, t_shell *shell, int arg_pos);
int			cd_barpoints(t_tokens token, t_shell *shell);
int			cd_prime(t_tokens token, t_shell *shell);
int			cd_minus(t_shell *shell);
int			cd_doubleminus(t_tokens token, t_shell *shell);
int			cd_doublepoints(t_shell *shell);
int			ft_env(t_shell *shell);
int			ft_echo(char **args, t_shell shell);
int			ft_exit(t_shell *shell);
int			ft_export(char **cmd_args, t_shell *shell);
int			ft_unset(char **cmd_args, t_shell *shell);
int			find_command(t_tokens *tkn, t_shell *shell);
int			add_exported_var(char *exported_var, t_shell *shell);
int			export_var(char *arg, t_shell *shell);
int			*tokenize_element_aux0(char *elem, t_tokens **former_token, int *arg_n, char **new_kind);
char		*search_for_kind(char *elem, char *former_kind);
char		*my_getenv(char *name, char **envp);
char		*command_generator(const char *text, int state);
char		**create_command_array(t_tokens *tokens);
char		**array_cpy(char **array);
char		**minishell_completion(const char *text, int start, int end);
t_tokens	*new_cmd_token(void);
t_tokens	*tokenize_everything(t_shell shell);

#endif
