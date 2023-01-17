# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 19:34:15 by harndt            #+#    #+#              #
#    Updated: 2023/01/15 11:58:48 by harndt           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# VARIABLES
# ==============================================================================

NAME	:=	data_compressor
BINARY	:=	decoder encoder
CC		:=	cc
CFLAGS	:=	-Wall -Wextra
HEADERS	:=	includes
SRCS	:=	./srcs/huffman_decoder.c	./srcs/huffman_encoder.c	\
			./srcs/huffman_tree.c		./srcs/huffman_utils.c
OBJS	:=	$(SRCS:.c=.o)

# ==============================================================================
# COLORS
# ==============================================================================

GREEN	:=	\033[1;32m
RED		:=	\033[1;31m
WHT		:=	\033[1;37m
EOC		:=	\033[1;0m

# ==============================================================================
# RULES
# ==============================================================================

all:	$(NAME)

%.o:	%.c
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME):	$(BINARY)

decoder:	srcs/huffman_decoder.o srcs/huffman_tree.o srcs/huffman_utils.o
	@$(CC) $(CFLAGS) ./srcs/huffman_decoder.o srcs/huffman_tree.o srcs/huffman_utils.o -I $(HEADERS) -o $@
	@echo "$(GREEN)DECODER compiled.$(EOC)"

encoder:	srcs/huffman_encoder.o srcs/huffman_tree.o srcs/huffman_utils.o
	@$(CC) $(CFLAGS) ./srcs/huffman_encoder.o srcs/huffman_tree.o srcs/huffman_utils.o -I $(HEADERS) -o $@
	@echo "$(GREEN)ENCODER compiled.$(EOC)"

clean:
	@echo "$(WHT)Removing .o files...$(EOC)"
	@rm -f $(OBJS)
	@echo "$(GREEN)Clean done.$(EOC)"

fclean:	clean
	@echo "$(WHT)Removing objects and binary files...$(EOC)"
	@rm -f $(BINARY)
	@echo "$(GREEN)Fclean done."

re:	fclean all

.PHONY:	all clean fclean re