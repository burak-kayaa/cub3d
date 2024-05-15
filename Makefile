SRCS	= main.c init.c mlx_funcs.c utils.c render.c draw.c move.c #key.c map.c parse.c render.c sprite.c texture.c utils.c
OBJS	= $(SRCS:.c=.o)

# Path: src/Makefile
NAME	= cub3D
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g -o3
RM		= rm -f
MLX		= ./mlx/libmlx.a
MLX_DIR	= ./mlx
LIBFT	= ./libft/libft.a
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L ./libft -lft -o $(NAME) 

$(LIBFT):
	make -j16 -C ./libft

$(MLX):
	make -j16 -C ./mlx 2> /dev/null

clean:
	$(RM) $(OBJS)
	make clean -C ./libft
	make clean -C ./mlx

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re