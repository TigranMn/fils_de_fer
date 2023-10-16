NAME			= fdf

SRC_DIR			= src

SRCS			= $(wildcard $(SRC_DIR)/*.c)

HEADER			= $(wildcard includes/*.h)

OBJS			= ${SRCS:.c=.o}

INCS			= -I

CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -g

FMS				= -framework OpenGL -framework AppKit -lmlx -lm 

all:	${NAME}

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) $(FMS) -o ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f ${NAME}

re: 	fclean all

.PHONY: all clean fclean mlx