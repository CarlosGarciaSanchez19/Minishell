/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/25 21:51:37 by carlosg2         ###   ########.fr       */
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
	char	*new_kd;
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

typedef struct s_pipes
{
	int	(*pipes)[2];
	int	num_pipes;
}	t_pipes;

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
void		create_pipes(t_pipes *p, t_tokens *tokens, t_shell *shell);
void		close_used_pipe(t_pipes *p, int i);
void		close_all_pipes(t_pipes *p);
void		redirect_input(char *file, t_tokens *current_tkn);
void		redirect_output(char *file, t_tokens *current_tkn);
void		append_output(char *file, t_tokens *current_tkn);
void		heredoc(t_tokens *tokens, t_shell *shell, char *str);
void		execute_tokens(t_tokens *tokens, t_shell *shell);
void		sigint_handler(int signum);
void		free_tokens(t_tokens *tokens);
void		error_pipe(t_tokens *tokens, t_shell *shell);
void		error_fork(t_tokens *tokens, t_shell *shell);
void		clean_bars(char *str);
void		bubble_sort(char **arr);
void		expand_env_vars(char **input, t_shell shell);
void		str_expansion(char **str, int prev_len, t_shell shell);
void		free_exec_vars(t_tokens *tokens, int (*pipes)[2]);
void		expand_env_vars(char **input, t_shell shell);
int			init_exec_vars_and_pipe_creat(t_tokens *tkns, t_pipes *p,
				t_shell *shell);
int			check_string(char **string, t_shell *shell);
int			check_quotes(t_tokens *start_token, int i, t_shell *shell);
int			error_file(char *string, char *arg, t_shell *shell);
int			error_option(char arg, t_shell *shell);
int			cd_error_args(t_shell *shell);
int			tkn_lst_size(t_tokens *tkn);
int			built_in(t_tokens *tkn, t_shell *shell);
int			is_built_in(t_tokens *tkn);
int			is_emptyquote(char *str);
int			count_quotes(char *str);
int			ft_pwd(t_shell *shell);
int			ft_cd(t_tokens token, t_shell *shell);
int			change_pwd(t_shell *shell, char *new_pwd);
int			cd_route(char **cmd_args, t_shell *shell, int arg_pos);
int			cd_barpoints(t_tokens token, t_shell *shell);
int			cd_prime(t_tokens token, t_shell *shell);
int			cd_minus(t_shell *shell);
int			cd_doubleminus(t_tokens token, t_shell *shell);
int			cd_doublepoints(t_shell *shell);
int			segment_route(t_tokens token, t_shell *shell);
int			ft_env(char **cmd_args, t_shell *shell);
int			ft_echo(char **args, t_shell shell);
int			ft_exit(char **cmd_args, t_shell *shell);
int			ft_export(char **cmd_args, t_shell *shell);
int			ft_unset(char **cmd_args, t_shell *shell);
int			find_command(t_tokens *tkn, t_shell *shell);
int			add_exported_var(char *exported_var, t_shell *shell);
int			export_var(char *arg, t_shell *shell);
int			tokenize_element_aux0(char *elem, t_tokens **former_token,
				char **new_kind);
char		*find_expand(char *str, int *n);
char		*search_for_kind(int i, char *former_kind, t_shell *shell);
char		*my_getenv(char *name, char **envp);
char		*command_generator(const char *text, int state);
char		**create_command_array(t_tokens *tokens);
char		**array_cpy(char **array);
char		**minishell_completion(const char *text, int start, int end);
t_tokens	*new_cmd_token(void);
t_tokens	*tokenize_everything(t_shell *shell);

#endif
