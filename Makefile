NAME = miniRT
LIBMLX = minilibx-linux/libmlx_Linux.a

SRCS = miniRT_main.c\
		calculate_vector/dimension_vectorcal.c

OBJS = $(SRCS:.c=.o)

CC = cc -fsanitize=address -fno-omit-frame-pointer

CFLAGS = -Wall -Wextra -Werror -I includes

all: $(NAME)

${NAME}: ${SRCS} ${LIBMLX}
	${CC} ${SRCS} ${LIBMLX} -lX11 -lXext -o ${NAME}

${LIBMLX}:
	make -C minilibx-linux/

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}
	make clean -C mlx/

re: fclean all

.PHONY:			all clean fclean re bonus