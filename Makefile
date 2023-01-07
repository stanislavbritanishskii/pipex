# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 18:24:12 by sbritani          #+#    #+#              #
#    Updated: 2023/01/07 04:04:39 by sbritani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = 	main.c utils.c paths.c pipes.c plumbs.c
NAME =  pipex
LIBFT	:= ./libft
OBJ	= $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT)/libft.a -o $(NAME)

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

norm:
	norminette $(SRCS) pipex.h

.PHONY: all clean fclean re norm libft