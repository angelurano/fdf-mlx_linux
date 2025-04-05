NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -g3 -fsanitize=address,leak,undefined # -O3

RM = rm -f

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = ./libs/mlx_linux
MINILIBX_FLAGS = -D LINUX -L$(MINILIBX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz # -o $(NAME) # -Imlx_linux

SRC_DIR = src
SRC = $(SRC_DIR)/checkinput.c  $(SRC_DIR)/color.c $(SRC_DIR)/fdf.c $(SRC_DIR)/init.c $(SRC_DIR)/parseinput.c
OBJ = $(SRC:.c=.o)

INCLUDES = -I./includes -I$(LIBFT_DIR)/includes -I$(MINILIBX_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR) re --no-print-directory
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIBX_FLAGS) -o $(NAME)

# %.o: %.c
#	$(CC) $(CFLAGS) -I/usr/include -I$(MINILIBX_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re bonus
