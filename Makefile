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
  $(SRC_DIR)/globals.c \
  \
  $(SRC_DIR)/lexer/create_token.c \
  $(SRC_DIR)/lexer/free_token.c \
  $(SRC_DIR)/lexer/create_lexer.c \
  $(SRC_DIR)/lexer/free_lexer.c \
  $(SRC_DIR)/lexer/run_lexer.c \
  $(SRC_DIR)/lexer/join_words.c \
  \
  $(SRC_DIR)/utils/b_varexists.c \
  $(SRC_DIR)/utils/b_fromenvp.c \
  $(SRC_DIR)/utils/b_unsetenv.c \
  $(SRC_DIR)/utils/b_getenv.c \
  $(SRC_DIR)/utils/b_setenv.c \
  $(SRC_DIR)/utils/ft_readline.c \
  $(SRC_DIR)/utils/ft_strjoin_free.c \
  $(SRC_DIR)/utils/linereader_free.c \
  $(SRC_DIR)/utils/ft_openrand.c \
  $(SRC_DIR)/utils/ft_openurand.c \
  $(SRC_DIR)/utils/ft_readint.c \
  $(SRC_DIR)/utils/ft_readlong.c \
  $(SRC_DIR)/utils/ft_readlonglong.c \
  $(SRC_DIR)/utils/ft_readuint.c \
  $(SRC_DIR)/utils/ft_readulong.c \
  $(SRC_DIR)/utils/ft_readullong.c \
  $(SRC_DIR)/utils/ft_readstr.c \
  $(SRC_DIR)/utils/ft_opentmp.c \
	$(SRC_DIR)/utils/print_prompt.c \
  \
  $(SRC_DIR)/parser/p_strerror.c \
  $(SRC_DIR)/parser/parser_init.c \
  $(SRC_DIR)/parser/parser_free.c \
  $(SRC_DIR)/parser/parser_parse.c \
  $(SRC_DIR)/parser/parser_to_list.c \
	\
  $(SRC_DIR)/base_commands/cd.c \
  $(SRC_DIR)/base_commands/echo.c \
  $(SRC_DIR)/base_commands/env.c \
  $(SRC_DIR)/base_commands/pwd.c \
  $(SRC_DIR)/base_commands/exit.c \
  $(SRC_DIR)/base_commands/export.c \
  $(SRC_DIR)/base_commands/unset.c \
  \
  $(SRC_DIR)/reader/reader_free.c \
  $(SRC_DIR)/reader/reader_init.c \
  $(SRC_DIR)/reader/handle_read.c \
  \
  $(SRC_DIR)/pipex/ft_pipex.c \
  $(SRC_DIR)/pipex/cmd_path.c \
  $(SRC_DIR)/pipex/ft_errors.c \
  $(SRC_DIR)/pipex/ft_utils.c \
  $(SRC_DIR)/pipex/ft_builtin.c \
  # TODO added $(SRC_DIR)/pipex/ft_builtin.c \ TODO
  
  
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
  $(TEST_DIR)/test_cd.c \
  $(TEST_DIR)/test_env.c \
  $(TEST_DIR)/test_pwd.c \
  $(TEST_DIR)/test_unset.c \
  $(TEST_DIR)/test_export.c \
  $(TEST_DIR)/test_exit.c \

OBJS     = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTOBJS = $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJD)/%.o,$(TESTS)) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/main.c,$(SRCS)))

LFT_DIR	 = $(OBJ_DIR)/libft/
_LIB_FT	 = $(LFT_DIR)libft.a
CRIT_DIR = $(OBJ_DIR)/criterion-2.4.2
CRIT_INC = $(CRIT_DIR)/include
CRIT_PC  = $(CRIT_DIR)/lib/pkgconfig/criterion.pc
CFLAGS   = -Wall -Wextra -Werror -g3 -std=c17 -I$(INC_DIR) -pipe -MMD -MP -I$(LFT_DIR)
LDFLAGS  = -O3 -g3 -std=c17 -pipe
TEST_CFLAGS = -I$(CRIT_INC)
TEST_LDFLAGS = -L$(CRIT_DIR)/lib -Wl,-rpath=$(CRIT_DIR)/lib -lcriterion


# Compiler preference: clang > gcc for main binary
ifeq ($(shell which clang),)
  $(shell echo "No suitable compiler found. Please install clang or gcc." >&2)
  CC = gcc
else
  $(shell echo "Using clang as the compiler." >&2)
  CC = clang
endif

# For tests, always use clang if available, else gcc (never zig cc)
ifeq ($(shell which clang),)
  TEST_CC = gcc
else
  TEST_CC = clang
endif

# If mold is installed, use it as the linker
ifneq ($(shell which mold),)
LDFLAGS += -fuse-ld=mold
endif

all: $(NAME)

$(NAME): $(_LIB_FT) $(OBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $(OBJS) $(_LIB_FT)"
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(_LIB_FT)

run_test: test
	@if [ "$(CRIT_DEV)" = "1" ]; then \
		./$(NTEST) --verbose; \
	else \
		./$(NTEST); \
	fi
test: $(NTEST)


$(NTEST): $(CRIT_PC) $(_LIB_FT) $(TESTOBJS)
	@echo "$(TEST_CC) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $(TESTOBJS) $(_LIB_FT)"
	@$(TEST_CC) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $(TESTOBJS) $(_LIB_FT)

$(_LIB_FT):
	@if [ ! -d $(LFT_DIR) ]; then \
		if command -v rad >/dev/null 2>&1; then \
			rad clone rad:z2r3ahNug1N33eWu4iD7NiuphqUL3 $(LFT_DIR); \
		else \
			git clone https://github.com/cliftontoaster-reid/libft $(LFT_DIR); \
		fi; \
	fi
	@$(MAKE) -C $(LFT_DIR) OBJ_DIR=$(abspath $(OBJ_DIR))/libft/build CC="$(CC)"

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
	@echo "$(TEST_CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@"
	@$(TEST_CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(NTEST)

re: fclean all

qre: clean all

bundle:
	@${MAKE} fclean
	@echo "Creating bundle for $(NAME)..."
	@if command -v bear >/dev/null 2>&1; then \
		echo "Using bear to generate compile_commands.json..."; \
		bear -- ${MAKE} all CC=cc; \
	else \
		${MAKE} all CC=cc; \
	fi
	@mkdir -p $(OBJ_DIR)/bundle
	@cp $(NAME) $(OBJ_DIR)/bundle/
	@cp LICENCE $(OBJ_DIR)/bundle/
	@cp README.md $(OBJ_DIR)/bundle/
	@cp compile_commands.json $(OBJ_DIR)/bundle/
	@cp $(SRC_DIR) $(OBJ_DIR)/bundle/ -r
	@cp $(INC_DIR) $(OBJ_DIR)/bundle/ -r
	@cp -r licenses $(OBJ_DIR)/bundle/
	@mkdir -p $(OBJ_DIR)/bundle/meta
	@cp .github/gift.opus $(OBJ_DIR)/bundle/meta/
	@mkdir -p $(OBJ_DIR)/release
	@echo "Creating uncompressed tar archive..."
	@tar -cf $(OBJ_DIR)/release/$(NAME).tar -C $(OBJ_DIR)/bundle .
	@echo "Creating compressed archives from tar..."
	@echo "  - tar.gz archive..."
	@gzip -c $(OBJ_DIR)/release/$(NAME).tar > $(OBJ_DIR)/release/$(NAME).tar.gz
	@echo "  - tar.xz archive..."
	@xz -c $(OBJ_DIR)/release/$(NAME).tar > $(OBJ_DIR)/release/$(NAME).tar.xz
	@echo "  - tar.lzma archive..."
	@xz --format=lzma -c $(OBJ_DIR)/release/$(NAME).tar > $(OBJ_DIR)/release/$(NAME).tar.lzma
	@echo "Creating zip archive..."
	@zip -r $(OBJ_DIR)/release/$(NAME).zip $(OBJ_DIR)/bundle >/dev/null
	@echo "Archives created in $(OBJ_DIR)/release/:"
	@ls -lh $(OBJ_DIR)/release/$(NAME).* | awk '{print "  - " $$9 " (" $$5 ")"}'
	@cd $(OBJ_DIR)/release && sha256sum $(NAME).* > $(NAME).checksums
	@if git config --get user.signingkey >/dev/null 2>&1 && command -v gpg >/dev/null 2>&1; then \
		echo "Signing archives with git signing key..."; \
		cd $(OBJ_DIR)/release && gpg --detach-sign --armor $(NAME).tar && \
		gpg --detach-sign --armor $(NAME).tar.gz && \
		gpg --detach-sign --armor $(NAME).tar.xz && \
		gpg --detach-sign --armor $(NAME).tar.lzma && \
		gpg --detach-sign --armor $(NAME).zip && \
		gpg --detach-sign --armor $(NAME).checksums; \
		echo "Digital signatures created (.asc files)"; \
	else \
		echo "Skipping signing (no git signing key configured or gpg not available)"; \
	fi

$(HOME)/.local/bin/trunk:
	@echo "Installing trunk..."
	@mkdir -p $(HOME)/.local/bin
	@curl -L https://trunk.io/releases/trunk -o $(HOME)/.local/bin/trunk
	@chmod +x $(HOME)/.local/bin/trunk
	@echo "Trunk installed successfully."
	@echo "Installing trunk tools..."
	@$(HOME)/.local/bin/trunk install
	@echo "Trunk tools installed successfully."

check: $(HOME)/.local/bin/trunk
	@echo "Running trunk check..."
	@$(HOME)/.local/bin/trunk check --all
	@echo "Trunk check completed."

.PHONY: all clean fclean re bundle
