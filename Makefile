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

CC = cc

CFLAGS	= -Wextra -Wall -Werror -g# -fsanitize=address # -v #-Wunreachable-code -Ofast -w

LIBMLXDIR	= ./lib/MLX42

LIBMLX = $(LIBMLXDIR)/build/libmlx42.a

LIBFTDIR = ./lib/libft

LIBFT	= $(LIBFTDIR)/libft.a

RM = rm -rf

HEADERS	= -I ./include -I $(LIBMLXDIR)/include -I $(LIBFTDIR)

LIBS	= $(LIBMLX) -ldl -lglfw -pthread -lm $(LIBFT)

SRCS	= main.c debug_utils.c parse_and_store.c \
			parser_utils.c fdf_init.c launch_mlx.c print.c \
			bresenham.c hooks.c project.c

OBJS	= $(SRCS:.c=.o)

GIT     = 	if !( [ -d $(LIBMLXDIR) ]); \
			then git clone https://github.com/Zzzhenya/MLX42.git $(LIBMLXDIR); \
			fi
# -mmacosx-version-min=12.6

all: $(NAME)

$(LIBMLX):
	@echo "...Checking for MLX42 repo."
	@$(GIT)
	@cmake $(LIBMLXDIR) -B $(LIBMLXDIR)/build && make -C  $(LIBMLXDIR)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "...fdf compiled."

clean:
	@$(RM) $(OBJS)
	@echo "...FDF OBJs cleaned."
	@$(MAKE) clean -C $(LIBFTDIR) 

fclean: clean
	@$(RM) $(NAME)
	@echo "...FDF binary cleaned."
	@$(RM) $(LIBMLXDIR)/build
	@echo "...MLX42 build files cleaned."
	@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all, clean, fclean, re
