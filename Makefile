# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 13:38:25 by mrabourd          #+#    #+#              #
#    Updated: 2023/05/10 16:01:48 by mrabourd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = 	main.c					\
		path.c					\
		env.c					\
		export.c				\
		eccho.c					\
		exit.c

SRC_ALL = ${addprefix ${SRC_DIR},${SRC}}

SRC_DIR = src/

OBJ_DIR = obj/

LIBFT_DIR = libft

OBJ_ALL = ${SRC_ALL:.c=.o}

OBJ = ${subst ${SRC_DIR}, ${OBJ_DIR}, ${OBJ_ALL}}

all : make_lib ${NAME}

make_lib :
	@make -C ${LIBFT_DIR}

${NAME} : ${OBJ}
	${CC} ${OBJ} -lreadline ${CFLAGS} libft/libft.a -o ${NAME}

${OBJ_DIR}%.o : ${SRC_DIR}%.c
	${CC} ${CFLAGS} -I/usr/include -c $< -o $@

clean :
	rm -f ${OBJ}

fclean : clean
	make -C ${LIBFT_DIR} fclean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re