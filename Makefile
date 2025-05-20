CC       = clang
INC_DIR  = ./include
SRC_DIR  = ./src
TEST_DIR = ./.test
OBJ_DIR  = ./target
TEST_OBJD= $(OBJ_DIR)/test
NAME     = minishell
NTEST    = minishell_test

SRCS     = $(shell find $(SRC_DIR) -type f -name '*.c')
# add the source files from SRCS to the test files excluding 'src/main.c'
TESTS = $(shell find $(TEST_DIR) -type f -name '*.c')

OBJS     = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTOBJS = $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJD)/%.o,$(TESTS)) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/main.c,$(SRCS)))

LFT_DIR	 = $(OBJ_DIR)/libft/
_LIB_FT	 = $(LFT_DIR)libft.a
CRIT_DIR = $(OBJ_DIR)/criterion-2.4.2
CRIT_INC = $(CRIT_DIR)/include
CRIT_PC  = $(CRIT_DIR)/lib/pkgconfig/criterion.pc
CFLAGS   = -Wall -Wextra -Werror -O3 -g3 -std=c17 -I$(INC_DIR) -pipe -MMD -MP -I$(LFT_DIR) -I$(CRIT_INC)
LDFLAGS  = -O3 -g3 -std=c17 -pipe
LDFLAGS += -L$(CRIT_DIR)/lib -Wl,-rpath=$(CRIT_DIR)/lib -lcriterion

# If clang is not installed, use gcc
ifeq ($(shell which clang),)
CC       = gcc
endif

# If mold is installed, use it as the linker
ifneq ($(shell which mold),)
LDFLAGS += -fuse-ld=mold
endif

all: $(NAME)

$(NAME): $(CRIT_PC) $(_LIB_FT) $(OBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $^"
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(_LIB_FT)

run_test: test
	@if [ "$(CRIT_DEV)" = "1" ]; then \
		./$(NTEST) --verbose; \
	else \
		./$(NTEST); \
	fi
test: $(NTEST)

$(NTEST): $(CRIT_PC) $(_LIB_FT) $(TESTOBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $^"
	@$(CC) $(LDFLAGS) -o $@ $(TESTOBJS) $(_LIB_FT)

$(_LIB_FT):
	@if [ ! -d $(LFT_DIR) ]; then git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); fi
	$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft/build

$(CRIT_PC):
	@mkdir -p $(OBJ_DIR)
	@wget https://github.com/Snaipe/Criterion/releases/download/v2.4.2/criterion-2.4.2-linux-x86_64.tar.xz -O $(CRIT_DIR).tar.xz;
	@tar -xf $(CRIT_DIR).tar.xz -C $(OBJ_DIR)
	@rm $(CRIT_DIR).tar.xz

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# Create the parent directory of the object file if it doesn't exist
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJD)/%.o: $(TEST_DIR)/%.c
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