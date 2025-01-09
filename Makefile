CC = clang

FLAGS = -g -Wall -Wextra -Werror

SRC = src/main.c \
	src/arguments.c \
	src/utils.c \
	src/init.c

NAME = philo

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: clean re