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

NAME = libcub.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c -g

AR = ar -rc

RAN = ranlib

SEPARATOR = "---------------------------------------------------------------"

CUB_DIR = cub/

CUB_SRCS =	event_handling/mouse_hooks.c \
			event_handling/keyboard_hhoks.c \
			game_v/game_v_reader.c \
			game_v/game_v_utilities.c \
			game_v/game_v_checks.c \
			game_v/sprites_utils.c \
			map/map_filler.c \
			map/map_checker.c \
			map/map_checker_utils.c \
			player/player_checker.c \
			player/player_mov.c \
			save/save.c \
			spell_caster/ray_caster1.c\
			spell_caster/ray_caster2.c \
			spell_caster/ray_casting.c \
			spell_caster/sprite_caster1.c \
			spell_caster/sprite_caster2.c \
			struct_manager/struct_cleaners1.c\
			struct_manager/struct_cleaners2.c\
			utils/string_utilities.c \
			utils/gen_utils.c \
			window_funcs/textures.c \
			window_funcs/win_func.c \

LIBFT_DIR = libft/

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
			get_next_line.c \
			ft_lstmap.c

BNS_DIR = cub/bonus/

BNS_SRCS = 	mini_map.c \
			mouse_rotation.c

CUB_DIRSRCS = $(addprefix ${CUB_DIR}, ${CUB_SRCS})

BNS_DIRSRCS = $(addprefix ${BNS_DIR}, ${BNS_SRCS})

OBJS = ${CUB_DIRSRCS:.c=.o}

LIBFT_DIRSRCS = $(addprefix ${LIBFT_DIR}, ${LIBFT_SRCS})

LIBFT_OBJS = ${LIBFT_DIRSRCS:.c=.o}

BNS_OBJS = $(BNS_DIRSRCS:.c=.o)

all: ${NAME}

$(NAME): ${OBJS} ${LIBFT_OBJS}
	@${AR} ${NAME} ${OBJS} ${LIBFT_OBJS}
	@${RAN} ${NAME}
	@mv ${NAME} cub
	@gcc -Werror -Wextra -Wall -lmlx -framework OpenGL -framework AppKit -g ./cub/${NAME} main.c -o cub3D

bonus: ${OBJS} ${LIBFT_OBJS} ${BNS_OBJS}
	@${AR} ${NAME} ${OBJS} ${LIBFT_OBJS} ${BNS_OBJS}
	@${RAN} ${NAME}
	@mv ${NAME} cub
	@gcc -Werror -Wextra -Wall -lmlx -framework OpenGL -framework AppKit -g ./cub/${NAME} cub/bonus/main_bonus.c -o cub3D

clean:
	@${RM} ${OBJS} $(BNS_OBJS) ${LIBFT_OBJS}

fclean: clean
	@${RM} ./cub/${NAME}
	@${RM} cub3d

re: fclean all

c: 
	@make re &> /dev/null
	@make clean &> /dev/null
	@${RM} ./cub/${NAME}
	@say -v Kyoko センパイを走らせて

karen:
	@echo "Karen is judging your header ${SEPARATOR}"
	@norminette libcub.h
	@echo "Karen is judging bonus${SEPARATOR}"
	@norminette cub/bonus
	@echo "Karen is judging event_handling${SEPARATOR}"
	@norminette cub/event_handling
	@echo "Karen is judging game_v${SEPARATOR}"
	@norminette cub/game_v
	@echo "Karen is judging map${SEPARATOR}"
	@norminette cub/map
	@echo "Karen is judging player${SEPARATOR}"
	@norminette cub/player
	@echo "Karen is judging save${SEPARATOR}"
	@norminette cub/save
	@echo "Karen is judging spell_caster${SEPARATOR}"
	@norminette cub/spell_caster
	@echo "Karen is judging struct_manager${SEPARATOR}"
	@norminette cub/struct_manager
	@echo "Karen is judging utils${SEPARATOR}"
	@norminette cub/utils
	@echo "Karen is judging window_funcs${SEPARATOR}"
	@norminette cub/window_funcs


.PHONY: all bonus clean fclean re
