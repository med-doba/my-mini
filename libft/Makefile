# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 17:41:58 by med-doba          #+#    #+#              #
#    Updated: 2022/10/10 21:27:10 by med-doba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOM = libft.a

CC = gcc

HEADER = libft.h

FLAGS = -Wall -Wextra -Werror

FCT = ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcat.c \
	  ft_putnbr_fd.c ft_strlcpy.c ft_substr.c \
	  ft_putstr_fd.c ft_strlen.c \
	  ft_isalnum.c ft_memcpy.c ft_split.c \
	  ft_isalpha.c ft_strchr.c ft_strncmp.c \
	  ft_strdup.c ft_isdigit.c ft_strcmp.c \
	  ft_putchar_fd.c ft_strjoin.c ft_strtrim.c \

OBJ = $(FCT:.c=.o)

$(NOM): $(OBJ)
	@ar -rc $(NOM) $(OBJ)

%.o : %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_BONUS)

fclean: clean
	@rm -rf $(NOM)

re: fclean all
all: $(NOM)
