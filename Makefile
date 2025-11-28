# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:54:19 by leramos-          #+#    #+#              #
#    Updated: 2025/11/20 12:44:49 by leramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project structure
NAME = pipex
SRCS_DIR = src
INCS_DIR = includes

# Libft structure
LIBFT_DIR = libft
LIBFT_SRCS_DIR = $(LIBFT_DIR)/src
LIBFT_INCS_DIR = $(LIBFT_DIR)/includes

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -I$(LIBFT_INCS_DIR)
AR = ar rcs
RM = rm -f

# Files
FILES = main exit utils initializing execute
LIBFT_LIB = $(LIBFT_DIR)/libft.a
OUT_FILE = $(NAME)

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $^ -o $(OUT_FILE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re