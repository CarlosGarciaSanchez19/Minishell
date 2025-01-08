# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 13:22:45 by carlosg2          #+#    #+#              #
#    Updated: 2025/01/08 15:37:31 by carlosg2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

INFO = "\033[1;34m[INFO]\033[0m"
SUCCESS = "\033[1;32m[✔️]\033[0m"
ERROR = "\033[1;31m[❌]\033[0m"

all: $(NAME)

libft/%.a:
	@cd libft && make && make clean

$(NAME): main.c libft/libft.a
	@echo $(INFO) "Compiling minishell... 🚀"
	@cc $(CFLAGS) main.c -lreadline -Llibft -lft -o $(NAME)
	@echo $(SUCCESS) "minishell compiled successfully 🎉"

clean:
	@echo $(INFO) "Cleaning up objects... 🧹"
	@rm -rf $(NAME)
	@echo $(SUCCESS) "Objects cleaned up successfully ✅"

fclean: clean
	@echo $(INFO) "Cleaning up minishell... 🗑️"
	@rm -rf $(NAME)
	@echo $(SUCCESS) "minishell cleaned up successfully ✅"

re: fclean all

.PHONY: all clean fclean re
