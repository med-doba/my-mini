NAME= minishell

CC= gcc

CFLAGS= -Wall -Wextra -Werror

CFILES = mini.c ft_lexer.c ft_lst_lexer.c ft_lst_env.c ft_parser.c \
		ft_environment.c ft_expand.c ft_expand_utils0.c ft_expand_utils1.c ft_lexer_scan.c \
		ft_lexer_utils1.c ft_lexer_utils0.c ft_scan_utils.c ft_execution.c ft_env.c ft_pwd.c \
		ft_export.c ft_echo.c ft_exit.c ft_unset.c ft_cd.c ft_built_in.c ft_redirection.c \
		ft_her_document.c ft_execution_utils.c ft_pipe.c ft_pipe_utils.c ft_extra.c\

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

LIBFT = libft/libft.a

INC= mini.h

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OFILES) $(LIBFT)
	@$(CC) $(OFILES) $(LIBFT) -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	@echo "minishell ok"

$(OBJ_DIR):
	@mkdir obj

$(OFILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(LIBFT): force
	@make -C libft

force:

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all
