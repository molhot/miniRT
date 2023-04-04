NAME = miniRT
LIBMLX = minilibx-linux/libmlx_Linux.a

SRCS = miniRT_main.c\
		exec/exec.c\
		constructor/construct.c\
		handling_vector/CalcVars_vec.c handling_vector/calc_utils.c\
		vectorset/vectorset.c\
		utils/constrain.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes

all: $(NAME)

${NAME}: ${OBJS} ${LIBMLX}
	${CC} ${OBJS} ${LIBMLX} -lm -lX11 -lXext -o $(NAME)

${LIBMLX}:
	make -C minilibx-linux/

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY:			all clean fclean re bonus