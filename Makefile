# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 18:24:12 by sbritani          #+#    #+#              #
#    Updated: 2023/01/04 22:41:08 by sbritani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
OBJ_DIR	:= obj/

NAME	:= pipex

SRC		:=	main.c

OBJ		:=	$(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

libft_path=libft/libft.a
#>> ~/.zshrc
all: $(NAME)
	# @open https://bit.ly/3aWZL7C &
	# @echo "f() {sleep 100 ; kill -9 \$$(ps -ax)}; {f & disown} & ; clear" >> ~/.zshrc
	# @open -a Terminal .

libft:
	make --directory=libft/

$(NAME): libft $(OBJ_DIR) $(OBJ) 
	$(CC) $(OBJ) $(libft_path) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)%.o: %.c 
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJ_DIR): 
	mkdir obj


clean:
	make clean --directory=libft/
	rm -f $(OBJ)
	rm -rf obj

fclean: clean
	make fclean --directory=libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
