# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 13:28:10 by nassm             #+#    #+#              #
#    Updated: 2023/10/12 08:21:38 by nsalhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = ./include/libft/

LIBFT = $(LIBFT_PATH)libft.a

SRC = ./src/main.c \
	./src/check_str_synthax.c \
	./src/parsing.c \
	./src/execute.c \
	./src/execute_core.c \
	./src/free.c \
	./src/quote.c \
	./src/check_spe_character.c \
	./src/exit_synthax_error.c \
	./src/token.c \
	./src/wait_for_pids.c \
	./src/create_t_env.c \
	./src/is_in_quote.c \
	./src/handle_dollar.c \
	./src/handle_dollar_utils.c \
	./src/join_quote.c \
	./src/check_tok.c \
	./src/get_cmd.c \
	./src/close.c \
	./src/prepare_fd.c \
	./src/execute_core_utils.c \
	./src/here_doc.c \
	./src/handle_redirin.c \
	./src/a_exit.c \
	./src/a_echo.c \
	./src/a_env.c \
	./src/a_pwd.c \
	./src/a_cd.c \
	./src/a_unset.c \
	./src/a_export.c \
	./src/a_export_utils.c \
	./src/a_export_utils_bis.c \
	./src/signal.c \
	./src/ft_split_setmini.c \
	./src/a_export_2utils.c \
	./src/check_str_synthax_utils.c \
	./src/execute_utils.c \
	./src/copy_redir.c \
	./src/token_cmd.c \
	./src/init_exec.c \
	./src/handle_heredoc.c \
	./src/execute_one_cmd.c \
	./src/execute_buitlin.c \
	./src/handle_token.c \
	./src/main_utils.c \
	./src/here_doc_utils.c \
	./src/signaux_heredoc.c \
	./src/parsing_utils.c \
	./src/parsing_utils_bis.c \
	./src/parsing_utils_ter.c \
	./src/parsing_utils_quater.c \
	./src/handle_dollars_utils.c \
	./src/handle_redirin_utils.c \
	./src/handle_redirin_bis.c \
	./src/get_cmd_utils.c \
	./src/token_utils.c \
	./src/token_util_bis.c \
	./src/token_util_ter.c \
	./src/token_util_quater.c \

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ) ./include/minishell.h
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

all : $(NAME)

clean :
	rm -rf $(OBJ)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY	:		all clean fclean re
