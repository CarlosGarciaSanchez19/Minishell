/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoriano <dsoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:33:36 by dsoriano          #+#    #+#             */
/*   Updated: 2025/02/10 18:10:12 by dsoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
	Este es un metodo que encontre en internet, en el que se crea un archivo temporal
	(que debería ser un archivo oculto).
*/
void	handle_dobinp(t_shell *shell, t_token *token)
{
    int     rd;
    int     fd;
    int     buf_size;
    char    *buf;

    fd = open(shell->tmpfile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
    buf_size = strlen(token->str);
    buf = malloc(buf_size + 1);
    printf("program: Start\n");
    rd = read(STDIN_FILENO, buf, buf_size);
    while (rd > 0)
    {
        buf[rd] = '\0';
        printf("program: Looping (read %s)", buf);
        if (strncmp(buf, token->str, buf_size + 1) == 0)
            break ;
        write(fd, buf, rd);
        rd = read(STDIN_FILENO, buf, buf_size);
    }
    free(buf);
    close(fd);
    shell->f_in = open(shell->tmpfile, O_RDONLY, 0777);
    dup2(shell->f_in, STDIN_FILENO);
    close(shell->f_in);
}

/*
	Pero Cris me ha dicho que eso luego es muy coñazo, con multiples pipes y tal,
	y que ellos mandaron el contenido directamente a una nueva pipe. Y te ahorras mallocs.
	Porque la pipe puede guardar temporalmente lo que le mandes y luego leer de ella.
*/
void	handle_heredoc(t_shell *shell, t_tokens *token)
{
	
}
