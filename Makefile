NAME = pipex

SRC = src/main.c src/ft_split.c src/utils.c

OBJS = ${SRC:%.c=%.o}

BONUS = src_bonus/main_bonus.c src_bonus/ft_split.c src_bonus/utils_bonus.c src_bonus/here_doc.c src_bonus/ft_putsmth.c src_bonus/gnl/get_next_line.c src_bonus/gnl/get_next_line_utils.c

BONUS_OBJS = ${BONUS:%.c=%.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

${NAME}: ${OBJS}
	${CC} ${FLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean ${NAME}

bonus: ${BONUS_OBJS}
	${CC} ${FLAGS} -o ${NAME} ${BONUS_OBJS}

.phony: all clean fclean re
