NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -O3

RM = rm -f

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ./libs/libft
LIBFT_I = $(LIBFT_DIR)/includes

MINILIBX = $(MINILIBX_DIR)/libmlx.a
MINILIBX_DIR = ./libs/mlx_linux
MINILIBX_I = $(MINILIBX_DIR)
MINILIBX_FLAGS = -D LINUX -L$(MINILIBX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC_DIR = src
SRC = $(SRC_DIR)/checkinput.c $(SRC_DIR)/color.c $(SRC_DIR)/fdf.c $(SRC_DIR)/handlers.c $(SRC_DIR)/init.c $(SRC_DIR)/lines.c $(SRC_DIR)/math_utils.c $(SRC_DIR)/parseinput.c $(SRC_DIR)/projection.c $(SRC_DIR)/render.c
OBJ = $(SRC:.c=.o)

INCLUDE_DIR = ./includes
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_I) -I$(MINILIBX_I) -I/usr/include

all: $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MINILIBX) $(LIBFT) $(MINILIBX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(MINILIBX):
	make -C $(MINILIBX_DIR) --no-print-directory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	norminette $(SRC_DIR) $(INCLUDE_DIR) $(LIBFT_DIR) $(LIBFT_I)

clean:
	make -C $(LIBFT_DIR) fclean --no-print-directory
	make -C $(MINILIBX_DIR) clean --no-print-directory
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

dev: CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -g3 -fsanitize=address,leak,undefined
dev: re

.PHONY: all clean fclean re
