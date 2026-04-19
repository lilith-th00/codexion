NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJ = codexion.o init.o parsing.o routine.o thread.o utils.o \
		monitor.o scheduler.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:re clean fclean re