# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 13:22:45 by carlosg2          #+#    #+#              #
#    Updated: 2025/03/06 19:24:07 by carlosg2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

BUILTINS = built-ins/cd.c built-ins/cd_aux_symbols.c built-ins/cd_aux_routes.c \
		   built-ins/echo.c \
		   built-ins/env.c \
		   built-ins/exit.c \
		   built-ins/export.c built-ins/export_aux_var_manag.c \
		   built-ins/pwd.c \
		   built-ins/unset.c \
		   built-ins/built-ins_utils.c

TOKENIZATION =	tokens_execution/execution.c \
				tokens_execution/execution_utils.c \
				tokens_execution/pipes_management.c \
				tokens_execution/specials_implemention.c \
				tokens_execution/heredoc.c \
				tokenize.c \
				tokenize_aux.c \
				tokenize_elem_aux.c

OTHERS =	error_handling.c \
			free_tokens.c \
			tab_completion.c \
			tab_complet_command.c \
			bubble_sort.c \

SRCS = $(BUILTINS) $(TOKENIZATION) $(OTHERS) init_and_free_shell.c signal_handlers.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

INFO = "\033[1;34m[INFO]\033[0m"
SUCCESS = "\033[1;32m[✔️]\033[0m"
ERROR = "\033[1;31m[❌]\033[0m"

%.o: SRCS
	@echo $(INFO) "Compiling objects..."
	@cc $(CFLAGS) -c $< -o $@

all: $(NAME)

libft/%.a:
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

$(NAME): $(OBJS) main.c libft/libft.a
	@echo $(INFO) "Compiling minishell... 🚀"
	@cc $(CFLAGS) main.c $(OBJS) -lreadline -Llibft -lft -o $(NAME)
	@echo $(SUCCESS) "minishell compiled successfully 🎉"

clean:
	@echo $(INFO) "Cleaning up objects... 🧹"
	@rm -rf $(OBJS)
	@echo $(SUCCESS) "Objects cleaned up successfully ✅"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(INFO) "Cleaning up minishell... 🗑️"
	@rm -rf $(NAME)
	@echo $(SUCCESS) "minishell cleaned up successfully ✅"

re: fclean all

.PHONY: all clean fclean re
