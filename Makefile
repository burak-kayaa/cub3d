MAN_PATH=./cub3d_src
BONUS_PATH=./cub3d_bonus_src
MAN_EXEC_NAME=cub3D
BONUS_EXEC_NAME=cub3D_bonus

all:
	@make -C $(MAN_PATH)

clean:
	@make clean -C $(MAN_PATH)
	@make clean -C $(BONUS_PATH)

fclean:
	@make fclean -C $(MAN_PATH)
	@make fclean -C $(BONUS_PATH)
	@if [ -e "$(MAN_EXEC_NAME)" ]; then \
		rm $(MAN_EXEC_NAME); \
	fi
	@if [ -e "$(BONUS_EXEC_NAME)" ]; then \
		rm $(BONUS_EXEC_NAME); \
	fi

bonus:
	@make -C $(BONUS_PATH)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean bonus re rebonus