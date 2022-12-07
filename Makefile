#######################################################
###### ARGUMENTS

NAME    =       so_long
CFLAGS  =       -Wextra -Wall -Werror -g3
CC      =       gcc
OBJS    =       $(SRCS:.c=.o)
MLX42   =       "../MLX42/libmlx42.a" -I include -lglfw -L "/Users/chabrune/.brew/opt/glfw/lib"
RM      =       rm -rf

#######################################################
###### SOURCES

SRCS       =	so_long.c

#######################################################
###### RULES

.c.o:
			gcc ${CFLAGS} -I include -I ../MLX42/include -c $< -o $(SRCS:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			gcc ${CFLAGS} ${OBJS} ${MLX42} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean re fclean