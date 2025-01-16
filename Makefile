NAME = fdf
CC = cc
CCFLAGS = -Wall -Wextra -Werror -Imlx
SRC = fdf.o get_next_line.o get_next_line_utils.o ft_split.o utils.o draw.o
MLX = mlx/libmlx.a -L/usr/lib -lXext -lX11 -g

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) $(MLX) -g

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@ 

compile:
	gcc -Wall -Wextra -Werror -Imlx -g -o fdf *.c

clean:
	rm -f $(SRC)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all bonus clean fclean
