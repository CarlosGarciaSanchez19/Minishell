/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main_splitquot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:45:42 by carlosg2          #+#    #+#             */
/*   Updated: 2025/01/23 16:53:38 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	**ft_splitquot(char const *str, char c);

int	main(int ac, char **av)
{
	char	*input;
	char	**command;

	if (ac == 1)
		return (1);
	input = av[1];
	command = ft_splitquot(input, ' ');
	while (*command)
	{
		printf("%s\n", *command);
		command++;
	}
	return (0);
}
