CC       = clang
INC_DIR  = ./include
SRC_DIR  = ./src
OBJ_DIR  = ./target
NAME     = minishell

SRCS     = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS     = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

LFT_DIR	 = $(OBJ_DIR)/libft/
_LIB_FT	 = $(LFT_DIR)libft.a
CFLAGS   = -Wall -Wextra -Werror -O3 -g3 -std=c17 -I$(INC_DIR) -pipe -MMD -MP -I$(LFT_DIR)
LDFLAGS += -O3 -g3 -std=c17 -pipe

# If clang is not installed, use gcc
ifeq ($(shell which clang),)
CC       = gcc
endif

# If mold is installed, use it as the linker
ifeq ($(shell which mold),)
LDFLAGS += -fuse-ld=mold
endif

all: $(NAME)

$(NAME): $(_LIB_FT) $(OBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $^"
	@$(CC) $(LDFLAGS) -o $@ $^ $(_LIB_FT)

$(_LIB_FT):
	@if [ ! -d $(LFT_DIR) ]; then git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); fi
	$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# Create the parent directory of the object file if it doesn't exist
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

qre: clean all

.PHONY: all clean fclean re