# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 09:11:04 by ppunzo            #+#    #+#              #
#    Updated: 2021/01/19 09:11:08 by ppunzo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c -g

AR = ar -rc

RAN = ranlib

SEPARATOR = "---------------------------------------------------------------"

PRINTF_SRCS =	ft_printf.c \
				ft_is_arg.c

LIBFT_DIR = ../libft/

LIBFT_SRCS =ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c
BNS_SRCS =	

OBJS = ${PRINTF_SRCS:.c=.o}

LIBFT_DIRSRCS = $(addprefix ${LIBFT_DIR}, ${LIBFT_SRCS})

LIBFT_OBJS = ${LIBFT_DIRSRCS:.c=.o}

BNS_OBJS = $(BNS_SRCS:.c=.o)

RM = rm -f

.o.c: ${CC} ${CFLAGS} $<

$(NAME): ${OBJS} ${LIBFT_OBJS}
	@${AR} ${NAME} ${OBJS} ${LIBFT_OBJS}
	@${RAN} ${NAME}

bonus: $(NAME)
	@ gcc $(CFLAGS) -c $(BNS_SRCS) -I ./
	@ ar rc $(NAME) $(BNS_OBJS)

all: ${NAME}

clean:
	@${RM} ${OBJS} $(BNS_OBJS) ${LIBFT_OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

c: 
	@make re &> /dev/null
	@make clean &> /dev/null

karen:
	@echo "Karen is judging your header ${SEPARATOR}"
	@norminette ${NAME:.a=.h}
	@echo "Karen is judging your pt1 & pt2 .c files ${SEPARATOR}"
	@norminette ${SRCS}
	@echo "Karen is judging your bouns .c files ${SEPARATOR}"
	@norminette ${BNS_SRCS}

.PHONY: all bonus clean fclean re
