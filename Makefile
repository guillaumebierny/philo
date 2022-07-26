SRC = philo.c routine_step.c utils.c check_end.c initialise.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
THREAD = -pthread

%.c: %.o
	$(CC) -c $^ -o $@
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

flcean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re clean fclean all 