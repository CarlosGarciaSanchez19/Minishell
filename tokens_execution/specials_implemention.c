/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials_implemention.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:26:46 by carlosg2          #+#    #+#             */
/*   Updated: 2025/03/13 15:02:57 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: File ", 12);
		write(2, file, ft_strlen(file));
		write(2, " could not be opened\n", 21);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(char *file)
{
	int	fd;

	fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		write(2, "Error: File ", 12);
		write(2, file, ft_strlen(file));
		write(2, " could not be opened\n", 21);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	append_output(char *file)
{
	int	fd;

	fd = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		write(2, "Error: File ", 12);
		write(2, file, ft_strlen(file));
		write(2, " could not be opened\n", 21);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
