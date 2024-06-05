# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asiercara <marvin@42.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 19:09:01 by asiercara         #+#    #+#              #
#    Updated: 2024/05/31 10:40:07 by anovio-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
MKDIR = mkdir

CC = gcc

LIBFTP = libft
PATHB = build/
PATHO = build/objs/
PATHS = src/
PATHSL = src/lexer/
PATHSP = src/parser/
PATHSB = src/builtins/
PATHSEX = src/expander/
PATHSU = src/utils/
PATHSE = src/errors/
PATHEX = src/executor/

BUILD_PATHS = $(PATHB) $(PATHO)

src	= 	src/main.c 								\
		src/lexer/tokenizer.c					\
		src/lexer/utils_lexer.c					\
		src/lexer/utils_nodes_lexer.c			\
		src/lexer/utils_nodes_aux.c				\
		src/parser/parser.c						\
		src/parser/redirections_parser.c		\
		src/parser/utils_parser.c				\
		src/parser/utils_nodes_parser.c			\
		src/executor/executor.c					\
		src/executor/hdoc.c						\
		src/executor/run_cmds.c					\
		src/executor/redirections.c				\
		src/executor/utils_executor.c			\
		src/utils/mini_live.c					\
		src/utils/verify_quotes.c				\
		src/expander/expander.c   				\
		src/expander/manage_quotes.c			\
		src/expander/calculate_len_for_malloc.c	\
		src/expander/expand_the_line.c			\
		src/expander/check_before_expansion.c	\
		src/expander/word_splitting.c			\
		src/expander/utils_expander.c 			\
		src/errors/parser_errors.c				\
		src/builtins/builtin_echo.c				\
		src/builtins/builtin_pwd.c	 			\
		src/builtins/builtin_env.c				\
		src/builtins/builtin_exit.c				\
		src/builtins/builtin_utils_nodes.c		\
		src/builtins/builtin_export.c			\
		src/builtins/builtin_export_helper.c	\
		src/builtins/builtin_unset.c			\
		src/builtins/builtin_cd.c				\
		src/utils/signals.c 					\
		#src/utils/utils.c						\


OBJS	=	$(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(src))))

FLAGS	=	-Wall -Werror -Wextra -g #-fsanitize=address

LIBFT	=	./libft/libft.a

HEADER	=	includes/minishell.h

READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib
	
INCLUDES =-Iincludes -I$(PATHP) -I$(LIBFTP) -I$(READLINE_DIR)/include 

all: $(BUILD_PATHS) $(NAME)

$(PATHO)%.o:: $(PATHS)%.c
	@echo "Compiling ${notdir $<}			in	$(PATHS)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHSL)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSP)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHSP)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSB)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHSB)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSEX)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHSEX)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHSU)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSE)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHSE)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHEX)%.c $(HEADER)
	@echo "Compiling ${notdir $<}			in	$(PATHEX)"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(NAME): $(LIBFT) $(OBJS) $(HEADER)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) $(READLINE_LIB) -o $(NAME)

	@echo "Success"

$(LIBFT):
	@$(MAKE) -C ./libft

$(PATHB):
	@$(MKDIR) $(PATHB)

$(PATHO):
	@$(MKDIR) $(PATHO)

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)
	@rm -f $(PATHB).tmp*
	@rmdir $(PATHO) $(PATHB)
	@make fclean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PRECIOUS: $(PATHO)%.o