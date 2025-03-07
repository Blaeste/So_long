#Param
MAKEFLAGS += --no-print-directory

CC			= gcc
FLAGS		= -Wall -Werror -Wextra -Iinc
MLXFLAGS	= -ldl -lglfw -pthread -lm

#Nom du programme
NAME	= so_long

# Obj des sous parties
LIBFT	= ./libft/libft.a
MLX		= ./MLX42/build/libmlx42.a

# Sources et obj main Makefile
SRCS	= src/so_long.c src/init.c src/utils.c src/check_map.c src/flood_fill.c src/mlx_utils.c  \
			src/mlx_utils2.c
		
OBJS	= ${SRCS:.c=.o}

#Regles
all:		${NAME}

.c.o:
			@${CC} ${FLAGS} -c $< -o $@

${LIBFT}:
			@make -C libft

${MLX}:
			@echo "🚀 Compiling minilibx..."
			@git clone https://github.com/codam-coding-college/MLX42.git > /dev/null 2>&1; \
			cd ./MLX42; \
			cmake -B build > /dev/null 2>&1; \
			cmake --build build -j4 > /dev/null 2>&1
			@echo "✅ minilibx Compiling done !\n"

${NAME}:	${MLX} ${OBJS} ${LIBFT}
			@${CC} ${FLAGS} ${OBJS} ${MLX} ${MLXFLAGS} ${LIBFT} -o ${NAME}
			@echo "✅ ${NAME} Compiling done !\n"

clean:
			@rm -rf MLX42
			@make fclean -C libft
			@rm -f ${OBJS}
			@echo "✅ (clean) Objects deleted !"

fclean:		clean
			@rm -f ${NAME}
			@echo "✅ (fclean) Program deleted !"

re:			fclean all

.PHONY:		all clean fclean re