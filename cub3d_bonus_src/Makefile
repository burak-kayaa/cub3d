SRCS	= check.c draw.c doors.c draw_helper.c init.c init_helper.c init_helper2.c ft_split_new_lines.c main.c mlx_funcs.c move.c move_helper.c render.c texture.c utils.c wall_check.c draw_sp.c load.c check_map.c check_map_helper.c flood_fill.c free.c doors_helper.c
OBJS	= $(SRCS:.c=.o)

# Path: src/Makefile
NAME	= cub3D_bonus
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f
MLX		= ../mlx/libmlx.a
MLX_DIR	= ../mlx
LIBFT	= ../libft/libft.a
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -L ../libft -lft -o $(NAME) 
	@cp $(NAME) ..

$(LIBFT):
	make -j16 -C ../libft

$(MLX):
	make -j16 -C ../mlx 2> /dev/null

clean:
	$(RM) $(OBJS)
	make clean -C ../libft
	make clean -C ../mlx

fclean: clean
	$(RM) $(NAME)
	make fclean -C ../libft

re: fclean all

shutup:
	killall afplay 2> /dev/null || true

.PHONY: all clean fclean re