NAME = philo_bonus

SRCS = $(wildcard *.c)
OBJS = ${SRCS:.c=.o}

CC = gcc
FLAGS = -Wall -Werror -Wextra
PTHREADS = -lpthread

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} ${PTHREADS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
