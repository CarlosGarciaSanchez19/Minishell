/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:23:00 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/09 16:47:23 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_shell
{
	char	**envp;
	char	*exit_status;
}	t_shell;

char	*my_getenv(char *name, char **envp);
int		ft_pwd(char **envp);
int		ft_cd(char **envp);
int		ft_env(char **envp);
int		ft_echo(char **command, char **envp);
int		ft_exit(char **envp);
int		ft_export(char **command, char **envp);
int		ft_unset(char **envp);

#endif
