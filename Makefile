CC = clang

FLAGS = -g -Wall -Wextra -Werror -lpthread

SRC = src/main.c \
	src/arguments.c \
	src/utils.c \
	src/init.c \
	src/mutexes.c

NAME = philo

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: clean re
