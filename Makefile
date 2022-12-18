# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 16:34:11 by chabrune          #+#    #+#              #
#    Updated: 2022/12/18 16:37:26 by chabrune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#######################################################
###### ARGUMENTS

NAME    	=       so_long
CFLAGS  	=       -Wextra -Wall -Werror -g3
CC      	=       gcc
MLX42   	=       "../MLX42/libmlx42.a" -I include -lglfw -L "/Users/chabrune/.brew/opt/glfw/lib"
RM      	=       rm -rf
FT_PRINTF 	=	"../ft_printf/libftprintf.a"
LIBFT		=	"../libft/libft.a"
OBJS    	=       $(SRCS:.c=.o)

#######################################################
###### SOURCES

SRCS       	=	so_long.c \

TASOEUR		= 	utils.c \
				get_next_line.c \
				get_next_line_utils.c \

#######################################################
###### RULES

.c.o:
			gcc ${CFLAGS} -I include -I ../MLX42/include -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C ../ft_printf
			gcc ${CFLAGS} ${FT_PRINTF} ${TASOEUR} ${OBJS} ${MLX42} -o ${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ../ft_printf

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C ../ft_printf fclean

re:			fclean all

.PHONY:		all clean re fclean