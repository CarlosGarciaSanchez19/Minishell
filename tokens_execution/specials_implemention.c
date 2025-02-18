/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials_implemention.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:26:46 by carlosg2          #+#    #+#             */
/*   Updated: 2025/02/18 12:27:03 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: File %s could not be opened\n", file);
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
		ft_printf("Error: File %s could not be opened\n", file);
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
		ft_printf("Error: File %s could not be opened\n", file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
