/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:19:31 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/29 16:23:36 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(int n_pipes,int pipes[n_pipes][2])
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipe(pipes[i]) < 0)
		{
			ft_printf("Error: Pipe could not be created\n");
			exit(1);
		}
		i++;
	}
}

void	pipes(int num_pipes, t_tokens *tokens) // Necesitamos crear un array de structs t_tokens
{
	int		(*pipes)[2]; // Si hace falta se declara en el main. Esto es un array de arrays de 2 ints cada uno (pipes).

	pipes = malloc(sizeof(int [2]) * num_pipes);
	if (!pipes)
	{
		ft_printf("Error: Pipes could not be created\n");
		exit(1);
	}
	create_pipes(num_pipes, pipes);
	while (num_pipes > 0)
	{
		// Aquí se ejecuta el comando
		num_pipes--;
	}
}
