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
  $(SRC_DIR)/main_extra.c \
  $(SRC_DIR)/print_tokens.c \
  $(SRC_DIR)/ft_prints.c \
  $(SRC_DIR)/globals.c \
	$(SRC_DIR)/remove_empty_commands.c \
  $(SRC_DIR)/init_shell.c \
  $(SRC_DIR)/read_input.c \
  $(SRC_DIR)/build_varnames_array.c \
  $(SRC_DIR)/expand_command_variables.c \
  $(SRC_DIR)/process_variable_expansion.c \
  $(SRC_DIR)/free_varlists.c \
  $(SRC_DIR)/process_commands.c \
  $(SRC_DIR)/cleanup_iteration.c \
  $(SRC_DIR)/cleanup_shell.c \
  \
  $(SRC_DIR)/lexer/create_token.c \
  $(SRC_DIR)/lexer/free_token.c \
  $(SRC_DIR)/lexer/create_lexer.c \
  $(SRC_DIR)/lexer/free_lexer.c \
  $(SRC_DIR)/lexer/run_lexer.c \
  $(SRC_DIR)/lexer/join_words.c \
  $(SRC_DIR)/lexer/lexer_none.c \
  $(SRC_DIR)/lexer/lexer_word.c \
  $(SRC_DIR)/lexer/lexer_uni.c \
  $(SRC_DIR)/lexer/lexer_duo.c \
  $(SRC_DIR)/lexer/lexer_special.c \
	$(SRC_DIR)/lexer/end_token.c \
  \
  $(SRC_DIR)/utils/b_varexists.c \
  $(SRC_DIR)/utils/b_fromenvp.c \
  $(SRC_DIR)/utils/b_unsetenv.c \
  $(SRC_DIR)/utils/b_getenv.c \
	$(SRC_DIR)/utils/b_getpid.c \
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
	$(SRC_DIR)/utils/ft_var.c \
  $(SRC_DIR)/utils/ft_opentmp.c \
	$(SRC_DIR)/utils/print_prompt.c \
	\
	$(SRC_DIR)/utils/env/str_equal.c \
	$(SRC_DIR)/utils/env/free_env_entry.c \
	$(SRC_DIR)/utils/env/set_pwd_to_current_dir.c \
	$(SRC_DIR)/utils/env/remove_env_node.c \
	$(SRC_DIR)/utils/env/is_matching_env.c \
	$(SRC_DIR)/utils/env/update_existing_var.c \
	$(SRC_DIR)/utils/env/add_new_env_var.c \
	\
	$(SRC_DIR)/utils/var/b_getenv_one.c \
	$(SRC_DIR)/utils/var/find_var_match.c \
	$(SRC_DIR)/utils/var/handle_special_var.c \
	$(SRC_DIR)/utils/var/count_unmatched_var.c \
	$(SRC_DIR)/utils/var/ft_strcpy.c \
	$(SRC_DIR)/utils/var/expand_matched_var.c \
	$(SRC_DIR)/utils/var/expand_unmatched_var.c \
	$(SRC_DIR)/utils/var/expand_special_var.c \
	$(SRC_DIR)/utils/var/iskey.c \
	$(SRC_DIR)/utils/var/num_places.c \
	$(SRC_DIR)/utils/var/handle_regular_char.c \
	$(SRC_DIR)/utils/var/handle_var_expansion.c \
	$(SRC_DIR)/utils/var/handle_dollar_char.c \
	$(SRC_DIR)/utils/var/copy_regular_char.c \
	$(SRC_DIR)/utils/var/handle_var_substitution.c \
	$(SRC_DIR)/utils/var/handle_dollar_substitution.c \
	$(SRC_DIR)/utils/var/replace_backspace_with_dollar.c \
  \
  $(SRC_DIR)/parser/p_strerror.c \
  $(SRC_DIR)/parser/parser_init.c \
  $(SRC_DIR)/parser/parser_free.c \
  $(SRC_DIR)/parser/parser_parse.c \
  $(SRC_DIR)/parser/parser_to_list.c \
  $(SRC_DIR)/parser/parser_handle_command.c \
  $(SRC_DIR)/parser/parser_handle_none.c \
  $(SRC_DIR)/parser/parser_special_pipe.c \
  $(SRC_DIR)/parser/parser_special_redirect_in.c \
  $(SRC_DIR)/parser/parser_special_redirect_out.c \
  $(SRC_DIR)/parser/parser_special_redirect_append.c \
  $(SRC_DIR)/parser/parser_special_redirect_heredoc.c \
  $(SRC_DIR)/parser/get_redirect_token.c \
	$(SRC_DIR)/parser/end_command.c \
	$(SRC_DIR)/parser/ft_lstget.c \
	\
  $(SRC_DIR)/base_commands/cd.c \
  $(SRC_DIR)/base_commands/echo.c \
  $(SRC_DIR)/base_commands/env.c \
  $(SRC_DIR)/base_commands/pwd.c \
  $(SRC_DIR)/base_commands/exit.c \
  $(SRC_DIR)/base_commands/export.c \
  $(SRC_DIR)/base_commands/unset.c \
	$(SRC_DIR)/base_commands/export/is_valid_identifier.c \
	$(SRC_DIR)/base_commands/export/print_exported_vars.c \
	$(SRC_DIR)/base_commands/export/export_with_value.c \
	$(SRC_DIR)/base_commands/export/export_without_value.c \
	$(SRC_DIR)/base_commands/export/export_variable.c \
  \
  $(SRC_DIR)/reader/reader_free.c \
  $(SRC_DIR)/reader/reader_init.c \
  $(SRC_DIR)/reader/handle_read.c \
  $(SRC_DIR)/reader/try_read.c \
  $(SRC_DIR)/reader/try_lex.c \
  $(SRC_DIR)/reader/try_parse.c \
  $(SRC_DIR)/reader/str_is_whitespace.c \
  $(SRC_DIR)/reader/handle_read_two.c \
  \
  $(SRC_DIR)/pipex/ft_pipex.c \
  $(SRC_DIR)/pipex/cmd_path.c \
  $(SRC_DIR)/pipex/ft_errors.c \
  $(SRC_DIR)/pipex/ft_utils.c \
  $(SRC_DIR)/pipex/ft_builtin.c \
	\
	$(SRC_DIR)/varextract/extract_var_list.c \
	\
	$(SRC_DIR)/git/find_git_dir.c \
	$(SRC_DIR)/git/is_repo.c \
	$(SRC_DIR)/git/get_branch_name.c \
	$(SRC_DIR)/git/read_head_file.c \
	$(SRC_DIR)/git/open_head_file.c \
	$(SRC_DIR)/git/git_getbranch.c \
	$(SRC_DIR)/git/is_git_changes.c \
	$(SRC_DIR)/git/is_git_changes_staged.c \
	$(SRC_DIR)/git/git_message.c \
	\
	$(SRC_DIR)/sigint/register_reader.c \
	$(SRC_DIR)/sigint/sigint_handler.c \
  
  
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
CFLAGS   = -Wall -Wextra -Werror -g3 -std=gnu17 -I$(INC_DIR) -pipe -MMD -MP -I$(LFT_DIR)
LDFLAGS  = -O3 -g3 -std=gnu17 -pipe -lreadline
TEST_CFLAGS = -I$(CRIT_INC)
TEST_LDFLAGS = -L$(CRIT_DIR)/lib -Wl,-rpath=$(CRIT_DIR)/lib -lcriterion

# Valgrind-compatible flags (no AddressSanitizer)
FSAN_CFLAGS   = -fsanitize=address -Wall -Wextra -Werror -g3 -std=gnu17 -I$(INC_DIR) -pipe -MMD -MP -I$(LFT_DIR)
FSAN_LDFLAGS  = -fsanitize=address -O0 -g3 -std=gnu17 -pipe -lreadline

BUNDLE_CFLAGS   = -Wall -Wextra -Werror -std=gnu17 -I$(INC_DIR) -pipe -MMD -MP -I$(LFT_DIR) -Os -flto -ffunction-sections -fdata-sections -fno-exceptions 
BUNDLE_LDFLAGS  = -std=gnu17 -pipe -lreadline -flto -Wl,--gc-sections -s -Wl,--as-needed

# Compiler preference: clang > gcc for main binary
ifeq ($(shell which clang),)
  CC = gcc
else
  CC = clang
endif

# If mold is installed, use it as the linker
ifneq ($(shell which mold),)
LDFLAGS += -fuse-ld=mold
endif

all: $(NAME)

# Fsanitize-compatible build (no AddressSanitizer)
fsanitize: CFLAGS = $(FSAN_CFLAGS)
fsanitize: LDFLAGS = $(FSAN_LDFLAGS)
fsanitize: fclean $(NAME)

$(NAME): $(OBJS)
	@echo "$(CC) $(LDFLAGS) -o $@ $(OBJS) $(_LIB_FT)"
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(_LIB_FT)

run_test: test
	@if [ "$(CRIT_DEV)" = "1" ]; then \
		./$(NTEST) --verbose; \
	else \
		./$(NTEST); \
	fi
test: $(NTEST)


$(NTEST): $(CRIT_PC) $(TESTOBJS)
	@echo "$(CC) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $(TESTOBJS) $(_LIB_FT)"
	@$(CC) $(LDFLAGS) $(TEST_LDFLAGS) -o $@ $(TESTOBJS) $(_LIB_FT)

$(_LIB_FT):
	@if [ ! -d $(LFT_DIR) ]; then \
		if command -v rad >/dev/null 2>&1; then \
			rad auth && rad node start && rad clone rad:z2r3ahNug1N33eWu4iD7NiuphqUL3 $(LFT_DIR); \
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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c  $(_LIB_FT)
# Create the parent directory of the object file if it doesn't exist
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(TEST_OBJD)/%.o: $(TEST_DIR)/%.c $(_LIB_FT)
# Create the parent directory of the object file if it doesn't exist
	@mkdir -p $(dir $@)
	@echo "$(CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) $(TEST_CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(NTEST)

re: fclean
	@$(MAKE) all -j$(shell nproc) CC=$(CC)
	@echo "Picoshell recompiled successfully."

qre: clean
	@$(MAKE) all -j$(shell nproc) CC=$(CC)
	@echo "Picoshell quick recompiled successfully."

bundle:
	@${MAKE} fclean
	@echo "Creating bundle for $(NAME)..."
	@if command -v bear >/dev/null 2>&1; then \
		echo "Using bear to generate compile_commands.json..."; \
		bear -- ${MAKE} test all CC=cc CFLAGS="$(BUNDLE_CFLAGS)" LDFLAGS="$(BUNDLE_LDFLAGS)" -j$(shell nproc); \
	else \
		${MAKE} all CC=cc CFLAGS="$(BUNDLE_CFLAGS)" LDFLAGS="$(BUNDLE_LDFLAGS)" -j$(shell nproc); \
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

format: $(HOME)/.local/bin/trunk
	@echo "Running trunk format..."
	@$(HOME)/.local/bin/trunk fmt --all
	@echo "Trunk format completed."

.PHONY: all clean fclean re bundle test run_test check format valgrind
