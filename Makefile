NAME = cub3d

SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/hehe.c \
	  $(SRC_DIR)/calculations.c \
	  $(SRC_DIR)/gen_utils.c \
	  $(SRC_DIR)/mlx_diy.c \
	  $(SRC_DIR)/simulation.c \
	  $(SRC_DIR)/calc_utils.c \
	  $(SRC_DIR)/render.c	\
	  $(SRC_DIR)/hook.c \
	  $(SRC_DIR)/rotations.c
#   $(SRC_DIR)/error.c \
	#   $(SRC_DIR)/parser.c \
	   $(SRC_DIR)/parser_utils.c 

CC = @cc
CFLAGS = -Wall -Wextra -Werror -lm -fsanitize=address -g

MLXFLAGS = -L. -lXext -L. -lX11

LIBFT_PATH = ./inc/libft
LIBFT = $(LIBFT_PATH)/libft.a

MINILIBX_PATH = ./inc/mlx_linux
MINILIBX = $(MINILIBX_PATH)/libmlx.a

OBJ_DIR = obj
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@echo "*-----------------*"
	@echo "|Compilation done!|"
	@echo "*-----------------*"

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

$(MINILIBX):
	@make -s -C $(MINILIBX_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "*--------------*"
	@echo "|Cleaning done!|"
	@echo "*--------------*"
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY:         all clean fclean re
