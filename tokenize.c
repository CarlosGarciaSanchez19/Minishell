/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:26:13 by dsoriano          #+#    #+#             */
/*   Updated: 2025/01/29 17:41:12 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_element(char *elem, t_tokens *former_token)
{
	int			i;

	i = 0;
	while (elem[i])
	{
		//hayq ue ver que tipo de token es
		if (search_for_pipe() == 1)
		{
			//en caso de pipe, hay que añadirsela al token de cmd previo
			//pero tambien hay que crear un nuevo struct (temp) conectado con el anterior,
			//y luego el nuevo se convierte en former y nos cargamos el temp
			former_token->cmd_pipe;
			t_tokens	*temp_token = new_cmd_token();
			former_token->next = temp_token;
			former_token = temp_token;
			destroy_temp_token();
		}
		else if (search_for_special() == 1)
		{
			//en caso de special, hay que detectar que tipo es y meterlo en el token de cmd previo
			former_token->;
		}
		else if (search_for_command() == 1)
		{
			//en caso de cmd, hay que meterlo en cmd del former_token

		}
		else
		{
			//en caso de argumento, hay que añadirlo al array de argumentos, en la posición siguiente
			former_token->cmd_args[j];
		}
	}
}

void	tokenize_everything(t_shell shell)
{
	int			i;
	t_tokens	former_token;

	i = 0;
	while (shell.user_input[i])
	{
		tokenize_element(shell.user_input[i], &former_token);
	}
}