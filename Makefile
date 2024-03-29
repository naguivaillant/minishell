# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 14:37:37 by nagvaill          #+#    #+#              #
#    Updated: 2023/06/18 18:41:54 by mrabourd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	src/
OBJ_DIR		=	obj/
DIR_LIB		=	./libft
NAMELFT		=	./libft/libft.a
NAME		=	minishell
INCLUDE		=	-I./include -I./libft/include
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
Make		=	Make

FILES = 	main					\
			path					\
			parsing_cmd				\
			split_list				\
			split_list_utils		\
			assign_type				\
			count					\
			env 					\
			export					\
			eccho					\
			unset					\
			exit					\
			aux						\
			check_is_builtin		\
			exec_builtins			\
			execution				\
			pipex					\
			pipex_direction			\
			pipex_utils				\
			safe_zone				\

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

OBJF = .cache_exists

$(OBJF):
	@mkdir -p $(OBJ_DIR)

all: make_lib $(NAME)

make_lib : 
	@make -C $(DIR_LIB)

$(OBJ_DIR)%.o	: $(SRC_DIR)%.c | $(OBJF)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME)    :    $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline libft/libft.a -o $(NAME)

clean    :
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJF)
	@cd $(DIR_LIB) && $(MAKE) clean

fclean    :    clean
	@rm -f $(NAME)

re        :    fclean all

.PHONY    :    all clean fclean re
