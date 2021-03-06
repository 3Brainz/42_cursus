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

CFLAGS = -Wall -Wextra -Werror -c

CMLXFLAGS = -Werror -Wextra -Wall -lmlx -framework OpenGL -framework AppKit

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

LIBUTILS_DIR = libutils/

LIBUTILS_SRCS =ft_memset.c \
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
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			get_next_line.c 

BNS_DIR = cub/bonus/

BNS_SRCS = 	mini_map.c \
			player_mov_bonus.c \
			mouse_rotation.c

CUB_DIRSRCS = $(addprefix ${CUB_DIR}, ${CUB_SRCS})

BNS_DIRSRCS = $(addprefix ${BNS_DIR}, ${BNS_SRCS})

OBJS = ${CUB_DIRSRCS:.c=.o}

LIBUTILS_DIRSRCS = $(addprefix ${LIBUTILS_DIR}, ${LIBUTILS_SRCS})

LIBUTILS_OBJS = ${LIBUTILS_DIRSRCS:.c=.o}

BNS_OBJS = $(BNS_DIRSRCS:.c=.o)

all: ${NAME}

$(NAME): ${OBJS} ${LIBUTILS_OBJS}
	@${AR} ${NAME} ${OBJS} ${LIBUTILS_OBJS}
	@${RAN} ${NAME}
	@mv ${NAME} cub
	@make -C cub/minilibx
	@cp cub/minilibx/libmlx.dylib .
	@${CC} ${CMLXFLAGS} ./cub/${NAME} cub/main.c libmlx.dylib -o cub3D

bonus: fclean ${OBJS} ${LIBUTILS_OBJS} ${BNS_OBJS}
	@${AR} ${NAME} ${OBJS} ${LIBUTILS_OBJS} ${BNS_OBJS}
	@${RAN} ${NAME}
	@mv ${NAME} cub
	@make -C cub/minilibx
	@cp cub/minilibx/libmlx.dylib .
	@${CC} ${CMLXFLAGS} ./cub/${NAME} cub/bonus/main_bonus.c libmlx.dylib -o cub3D

clean:
	@${RM} ${OBJS} $(BNS_OBJS) ${LIBUTILS_OBJS}
	@make clean -C cub/minilibx

fclean: clean
	@${RM} ./cub/${NAME}
	@${RM} libmlx.dylib
	@${RM} cub3d

re: fclean all

c: 
	@make re &> /dev/null
	@make clean &> /dev/null
	@${RM} ./cub/${NAME}
	@say -v Kyoko センパイを走らせて

karen:
	@echo "Karen is judging your header ${SEPARATOR}\n"
	@norminette -R CheckDefine cub/libcub.h
	@echo "\n"
	@echo "Karen is judging bonus${SEPARATOR}\n"
	@norminette cub/bonus
	@echo "\n"
	@echo "Karen is judging event_handling${SEPARATOR}\n"
	@norminette cub/event_handling
	@echo "\n"
	@echo "Karen is judging game_v${SEPARATOR}\n"
	@norminette cub/game_v
	@echo "\n"
	@echo "Karen is judging map${SEPARATOR}\n"
	@norminette cub/map
	@echo "\n"
	@echo "Karen is judging player${SEPARATOR}\n"
	@norminette cub/player
	@echo "\n"
	@echo "Karen is judging save${SEPARATOR}\n"
	@norminette cub/save
	@echo "\n"
	@echo "Karen is judging spell_caster${SEPARATOR}\n"
	@norminette cub/spell_caster
	@echo "\n"
	@echo "Karen is judging struct_manager${SEPARATOR}\n"
	@norminette cub/struct_manager
	@echo "\n"
	@echo "Karen is judging utils${SEPARATOR}\n"
	@norminette cub/utils
	@echo "\n"
	@echo "Karen is judging window_funcs${SEPARATOR}\n"
	@norminette cub/window_funcs
	@echo "\n"
	@echo "Karen is judging main${SEPARATOR}\n"
	@norminette cub/main.c


.PHONY: all bonus clean fclean re
