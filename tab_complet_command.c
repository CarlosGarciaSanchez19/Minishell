/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_complet_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:45:54 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/27 12:46:01 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_built_ins(void)
{
	char			*built_ins[8];
	static int		i = -1;

	built_ins[0] = "pwd";
	built_ins[1] = "cd";
	built_ins[2] = "env";
	built_ins[3] = "echo";
	built_ins[4] = "exit";
	built_ins[5] = "export";
	built_ins[6] = "unset";
	built_ins[7] = NULL;
	i++;
	if (i == 8)
		i = 0;
	return (built_ins[i]);
}

static	char	*command_tab_search(DIR	*dp, char	*text)
{
	struct dirent	*entry;
	char			*built_in;

	entry = readdir(dp);
	built_in = search_built_ins();
	while (entry)
	{
		if (ft_strncmp(entry->d_name, text, ft_strlen(text)) == 0)
			return (ft_strdup(entry->d_name));
		if (built_in && ft_strncmp(built_in, text, ft_strlen(text)) == 0)
			return (ft_strdup(built_in));
		built_in = search_built_ins();
		entry = readdir(dp);
	}
	return (NULL);
}

static char	**initial_config(int state, char **paths, int *index, DIR **dp)
{
	if (state == 0)
	{
		if (paths)
			ft_free_multiarray((void **)paths);
		paths = ft_split(getenv("PATH"), ':');
		*index = 0;
		*dp = NULL;
	}
	return (paths);
}

char	*command_generator(const char *text, int state)
{
	static char		**paths = NULL;
	static int		index = 0;
	static DIR		*dp = NULL;
	char			*command;

	paths = initial_config(state, paths, &index, &dp);
	while (paths && paths[index])
	{
		if (!dp)
			dp = opendir(paths[index]);
		if (!dp)
		{
			index++;
			continue ;
		}
		command = command_tab_search(dp, (char *)text);
		if (command)
			return (command);
		closedir(dp);
		dp = NULL;
		index++;
	}
	return (NULL);
}
