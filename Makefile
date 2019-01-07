# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktlili <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/10 23:32:37 by ktlili            #+#    #+#              #
#    Updated: 2018/10/13 01:14:09 by ktlili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = src

LEX_PATH = src/lexer

SRC_NAME =	main.c \
			util.c \
			util2.c \
			clean_path.c \
			parser.c \
			execute.c \
			changedir.c \
			spawn_bin.c \
			env_handler.c \
			env_lst_util2.c \
			ft_env.c \
			ft_env_tools.c \
			expand_tokens.c \
			cd_l_p.c \
			cd_tools.c \
			expand_dollar.c \
			env_lst_util.c \
			path_tools.c \
			bin_path.c \
			dynamic_buff.c

SRC_LEX = scanner.c jump_table.c ft_realloc.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o) $(SRC_LEX:.c=.o)

LIB = ./lib/libft.a

FLAGS = -ggdb -Wall -Wextra -Werror

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all:	$(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./lib/
	gcc $(OBJ) $(LIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	gcc -I. $(FLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o: $(LEX_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	gcc -I. $(FLAGS) -o $@ -c $<

clean:
	$(MAKE) -C ./lib/ clean
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) -C ./lib/ fclean
	/bin/rm -f $(NAME)

re: fclean all
