/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/23 16:26:23 by carlosg2         ###   ########.fr       */
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
	char	**envp;
	char	*pwd;
	char	*path;
	int		exit_status;
}	t_shell;

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
