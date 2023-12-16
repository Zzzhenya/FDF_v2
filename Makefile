# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:45:13 by sde-silv          #+#    #+#              #
#    Updated: 2023/11/13 15:45:17 by sde-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -g -fsanitize=address # -v #-Wunreachable-code -Ofast -w
LIBMLX	= ./lib/MLX42
LIBFT	= libft.a
CC = cc

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm $(LIBFT) # -pthread -lm $(LIBFT)
SRCS	= main.c debug_utils.c parse_and_store.c \
			parser_utils.c fdf_init.c launch_mlx.c print.c \
			bresenham.c hooks.c project.c
OBJS	= $(SRCS:.c=.o)
GIT     = 	if !( [ -d $(LIBMLX) ]); \
			then git clone https://github.com/Zzzhenya/MLX42.git $(LIBMLX); \
			fi
# -mmacosx-version-min=12.6

all: libmlx libft $(NAME)

libmlx:
	@echo "...Checking for MLX42 repo."
	@$(GIT)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C ./lib/libft
	@cp lib/libft/$(LIBFT) $(LIBFT) 
	@cp lib/libft/libft.h include/libft.h

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "...fdf compiled."

clean:
	@rm -rf $(OBJS)
	@echo "...FDF OBJs cleaned."
	@$(MAKE) clean -C ./lib/libft

fclean: clean
	@rm -rf $(NAME)
	@echo "...FDF binary cleaned."
	@rm -rf $(LIBMLX)/build
	@echo "...MLX42 build files cleaned."
	@$(MAKE) fclean -C ./lib/libft
	@rm ./include/libft.h
	@rm -f libft.a

re: clean all

.PHONY: all, clean, fclean, re
