/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_completion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:46:59 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/27 13:00:56 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*file_and_dir_management(char *directory, char *entry_name)
{
	char		*full_path;
	char		*tmp;
	struct stat	file_stat;

	tmp = ft_strjoin(directory, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, entry_name);
	if (!full_path)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	if (stat(full_path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		free(full_path);
		return (ft_strjoin(entry_name, "/"));
	}
	free(full_path);
	return (ft_strdup(entry_name));
}

char	*filename_generator(const char *text, int state)
{
	static DIR				*dp = NULL;
	static struct dirent	*entry;
	static char				*directory = NULL;

	if (state == 0)
	{
		free(directory);
		directory = getcwd(NULL, 0);
		if (!directory)
			return (NULL);
		dp = opendir(directory);
	}
	if (!dp)
		return (NULL);
	entry = readdir(dp);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, (char *)text, ft_strlen(text)) == 0)
			return (file_and_dir_management(directory, entry->d_name));
		entry = readdir(dp);
	}
	closedir(dp);
	dp = NULL;
	return (NULL);
}

char	**minishell_completion(const char *text, int start, int end)
{
	(void)end;
	if (start == 0)
		return (rl_completion_matches(text, command_generator));
	rl_completion_append_character = '\0';
	return (rl_completion_matches(text, filename_generator));
}
