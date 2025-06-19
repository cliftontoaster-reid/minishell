CC       = clang
INC_DIR  = ./include
SRC_DIR  = ./src
TEST_DIR = ./.test
OBJ_DIR  = ./target
TEST_OBJD= $(OBJ_DIR)/test
NAME     = minishell
NTEST    = minishell_test

SRCS     = \
  $(SRC_DIR)/main.c \
  \
  $(SRC_DIR)/lexer/create_token.c \
  $(SRC_DIR)/lexer/free_token.c \
  $(SRC_DIR)/lexer/create_lexer.c \
  $(SRC_DIR)/lexer/free_lexer.c \
  $(SRC_DIR)/lexer/run_lexer.c \
  $(SRC_DIR)/lexer/join_words.c \
  \
  $(SRC_DIR)/utils/b_varexists.c \
  $(SRC_DIR)/utils/b_getenv.c \
  $(SRC_DIR)/utils/b_setenv.c \
  $(SRC_DIR)/utils/b_fromenvp.c \
  $(SRC_DIR)/utils/b_unsetenv.c \
  $(SRC_DIR)/utils/ft_strjoin_free.c \
  $(SRC_DIR)/utils/ft_readline.c \
  $(SRC_DIR)/utils/linereader_free.c \
  \
  $(SRC_DIR)/parser/parser_init.c \
  $(SRC_DIR)/parser/parser_free.c \
  $(SRC_DIR)/parser/parser_parse.c \
  \
  $(SRC_DIR)/reader/reader_free.c \
  $(SRC_DIR)/reader/reader_init.c \
  $(SRC_DIR)/reader/handle_read.c \

 # add the source files from SRCS to the test files excluding 'src/main.c'
TESTS = \
  $(TEST_DIR)/test_lexer_basic.c \
  $(TEST_DIR)/test_lexer_redirections.c \
  $(TEST_DIR)/test_lexer_quotes.c \
  $(TEST_DIR)/test_lexer_complex.c \
  $(TEST_DIR)/test_join_words.c \
  $(TEST_DIR)/test_lexer_utils.c \
  $(TEST_DIR)/test_b_fromenvp.c \
  $(TEST_DIR)/test_b_getenv.c \
  $(TEST_DIR)/test_b_setenv.c \
  $(TEST_DIR)/test_b_unsetenv.c \
  $(TEST_DIR)/test_b_varexists.c \
  $(TEST_DIR)/test_parser_basic.c \
  $(TEST_DIR)/test_parser_pipe.c \
  $(TEST_DIR)/test_utils.c \
  $(TEST_DIR)/test_utils_string.c \
  $(TEST_DIR)/test_utils_readline.c \

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
	@rm -f $(NAME) $(NTEST)

re: fclean all

qre: clean all

.PHONY: all clean fclean re