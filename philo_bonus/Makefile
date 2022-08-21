SRC = main.c check_end.c initialisation.c ft_atoi.c \
		utils.c
OBJ = $(SRC:.c=.o)
CC = gcc $(CFLAGS)
NAME = philo_bonus
THREAD = -pthread
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) -o $(<:.c=.o) -c $<

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(THREAD) -o $(NAME)

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re clean fclean all
