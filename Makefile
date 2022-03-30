NAME			= cub3D
CC				= clang
RM				= rm -rf
OS				= $(shell uname)

CFLAGS			= -Wall -Werror -Wextra
IFLAGS			= -I$(MLX_DIR) -I$(INC_DIR) -I$(LIBFT_DIR)/includes
LINK_FLAGS		= -L $(MLX_DIR) -lmlx -L $(LIBFT_DIR) -lft -framework OpenGL -framework Appkit

SRC_DIR			= srcs
INC_DIR			= includes
MLX_DIR			= mlx
LIBFT_DIR		= LIBFT
OBJ_DIR			= objs
BONUS_DIR		= bonus

INC				= $(shell find $(INC_DIR) -type f -name "*.h")
SRC				= $(notdir $(shell find $(SRC_DIR) -type f -name "*.c"))
OBJ				= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
vpath			%.c $(shell find $(SRC_DIR) -type d)

_YELLOW         = \033[38;5;184m
_GREEN          = \033[38;5;46m
_RESET          = \033[0m
_INFO           = [$(_YELLOW)INFO$(_RESET)]
_SUCCESS        = [$(_GREEN)SUCCESS$(_RESET)]
_CLEAR          = \033[2K\c

ifeq ($(OS), Linux)
	MLX_DIR = mlx_linux
	IFLAGS = -I/usr/include -I$(MLX_DIR) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -D LINUX=1
	LINK_FLAGS = -L $(MLX_DIR) -lmlx_Linux -L /usr/lib -lXext -lX11 -lm -lz -L $(LIBFT_DIR) -lft
endif

all				: init $(NAME)
				@echo "$(_SUCCESS) Compilation done"

init			: 
				@$(shell mkdir -p $(OBJ_DIR))
				@$(MAKE) --silent -C $(LIBFT_DIR)
				@echo "$(_INFO) Preparing to initialize mlx..."
				@$(MAKE) --silent -C $(MLX_DIR)
				@echo "$(_SUCCESS) mlx compiled !"

$(NAME)			: $(OBJ)
				@echo "$(_INFO) Intializing $(NAME)"
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ $^ $(LINK_FLAGS) 

$(OBJ_DIR)/%.o	: %.c
				@echo "\t$(_YELLOW)Compiling $(_RESET) $*.c\r\c"
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
				@echo "$(_CLEAR)"

clean			:
				@echo "$(_INFO) Deleting object files and directories..."
				@$(RM) $(OBJ_DIR)
				@$(MAKE) clean --silent -C $(LIBFT_DIR)
				@$(MAKE) clean --silent -C $(MLX_DIR)
				@echo "$(_SUCCESS) Working directory cleaned"

fclean			:
				@echo "$(_INFO) Deleting object files directories and more..."
				@$(RM) $(OBJ_DIR)
				@$(RM) $(NAME)
				@$(MAKE) fclean --silent -C $(LIBFT_DIR)
				@$(MAKE) clean --silent -C $(MLX_DIR)
				@$(MAKE) fclean --silent -C $(BONUS_DIR)
				@echo "$(_SUCCESS) Working directory cleaned"

re				: fclean all

.SUFFIXES:		.c .o .h
.PHONY:			all clean fclean re bonus