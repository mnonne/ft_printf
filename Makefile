# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/09 18:05:08 by aminadzh          #+#    #+#              #
#    Updated: 2018/02/19 17:23:46 by aminadzh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CFLAGS	= -Wall -Wextra -Werror
CC		= gcc

LIB_DIR	= ./libft
SRC_DIR	= ./src
INC_DIR	= ./inc
BIN_DIR	= bin

SRC		= char_conversion.c \
			ft_printf.c \
			handler.c \
			hex_conversion.c \
			int_convertion.c \
			oct_conversion.c \
			specs.c \
			str_conversion.c \
			uint_conversion.c \
			ft_intmaxtoa.c

SRCS 	= $(addprefix $(SRC_DIR)/,$(SRC))

OBJS	= $(addprefix $(BIN_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB_DIR)
	@cp ./libft/*.o ./bin
	@ar rcs $@ $(BIN_DIR)/*.o
	@echo "LIBFTPRINTF is ready to use"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(BIN_DIR)
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIB_DIR)
	@rm -rf bin

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

test: re
	@gcc -Wall -Wextra -Werror -o test.out tests/main.c -I./includes -L. -lftprintf
	@./test.out
