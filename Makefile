NAME = fdf
CC = cc
CCFLAGS = -Wall -Wextra -Werror
SRC = fdf.o get_next_line.o get_next_line_utils.o ft_split.o utils.o

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) -g

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@

compile:
	gcc -Wall -Wextra -Werror -g -o fdf *.c

clean:
	rm -f $(SRC)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all bonus clean fclean
