NAME = philo

SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lpthread

clean:
	@rm $(OBJ)

fclean: clean
	@rm $(NAME)

re: fclean all

.PHONY:all fclean clean re
