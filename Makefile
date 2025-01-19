CC = clang

FLAGS = -g -Wall -Wextra -Werror -pthread

SRC = src/main.c \
	src/arguments.c \
	src/utils.c \
	src/init.c \
	src/mutexes.c \
	src/action.c \
	src/cleanup.c

NAME = philo

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: clean re
