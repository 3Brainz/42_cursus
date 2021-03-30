# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 18:22:10 by ppunzo            #+#    #+#              #
#    Updated: 2021/03/16 18:22:19 by ppunzo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a
PROGNAME = test
NM = nasm
NFLAGS = -f macho64
AR = ar -rc
RAN = ranlib
SRCS =	ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_write.s \
		ft_read.s	\
		ft_strdup.s
RM = rm -rf
CC = gcc
CFLAGS = -Werror -Wextra -Wall

OBJS = ${SRCS:.s=.o}

%.o:%.s
	$(NM) $(NFLAGS) $<

all : ${NAME}

${NAME} : ${OBJS}
	@${AR} ${NAME} ${OBJS}
	@${RAN} ${NAME}

clean :
	@${RM} ${SRCS:.s=.o}

fclean : clean
	@${RM} ${NAME}

compile : re clean
	@${CC} ${CFLAGS} ${NAME} main.c -o ${PROGNAME}

test : compile
	./${PROGNAME}
	@${RM} ${PROGNAME}
	@make fclean

re : fclean all