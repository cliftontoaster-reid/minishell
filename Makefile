CC       = clang
INC_DIR  = ./include
SRC_DIR  = ./src
OBJ_DIR  = ./target
CFLAGS   = -Wall -Wextra -Werror -O3 -g3 -std=c17 -I$(INC_DIR) -pipe -MMD -MP
LDFLAGS += -O3 -g3 -std=c17 -pipe
NAME     = minishell
SRCS     = $(wildcard $(SRC_DIR)/*.c)
OBJS     = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# If clang is not installed, use gcc
ifeq ($(shell which clang),)
CC       = gcc
endif

# If mold is installed, use it as the linker
ifeq ($(shell which mold),)
LDFLAGS += -fuse-ld=mold
endif

$(NAME): $(OBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $^"
	@$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re