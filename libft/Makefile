# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/21 13:49:12 by carlosg2          #+#    #+#              #
#    Updated: 2025/03/18 16:48:04 by carlosg2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isquote.c ft_strisalnum.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_printf_utils.c ft_strcmp.c \
	ft_strisnumber.c ft_atod.c ft_arraylen.c ft_freearray.c ft_free_multiarray.c \
	get_next_line.c ft_strndup.c ft_strcpy.c ft_splitquot.c ft_realloc.c in_quot.c ft_strishasquote.c

BSRCS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:%.c=%.o)
BOBJS = $(BSRCS:%.c=%.o)

INFO = "\033[1;34m[INFO]\033[0m"
SUCCESS = "\033[1;32m[✔️]\033[0m"

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

AR = ar rcs

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(INFO) "Compiling libft..."
	@$(AR) $(NAME) $(OBJS)
	@echo $(SUCCESS) "Libft compiled!"

bonus: $(OBJS) $(BOBJS)
	@$(AR) $(NAME) $(OBJS) $(BOBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $(SRCS) $(BSRCS)

clean:
	@$(RM) $(OBJS) $(BOBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
