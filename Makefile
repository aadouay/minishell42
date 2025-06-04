CC = cc
NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Werror -Wextra -Iincludes

SRC_FILES = minishell.c \
			parsing/parsing.c \
			parsing/lexer/tokens.c \
			parsing/lexer/lexer_core.c \
			parsing/lexer/lexer_init.c \
			parsing/lexer/handle_unquoted_word.c \
			parsing/lexer/lexer_utils.c \
			parsing/parser/parser_helpers.c \
			parsing/parser/parser_core.c \
			parsing/parser/parser_init.c \
			parsing/parser/grammar.c \
			parsing/lexer/lexer.c \
			parsing/lexer/expantion/expander.c \
			parsing/lexer/expantion/expander_utils.c \
			parsing/lexer/heredoc/heredoc.c \
			parsing/lexer/heredoc/heredoc_utils.c \
			parsing/lexer/heredoc/heredoc_expantion.c \
			execution/executor.c \
			execution/pipe_helper/exe_first.c \
			execution/pipe_helper/exe_last_cmd.c \
			execution/pipe_helper/exe_middle.c \
			execution/pipe_helper/set_end.c \
			execution/pipe.c \
			execution/redir_for_single.c \
			execution/redir_for_multi.c \
			execution/help_sredir/redir_append.c \
			execution/help_sredir/redir_herdoc.c \
			execution/help_sredir/redir_infile.c \
			execution/help_sredir/redir_outfile.c \
			execution/help_sredir/show_ambigu.c \
			execution/help_mredir/show_amb2.c \
			execution/help_mredir/redir_append2.c \
			execution/help_mredir/redir_herdoc2.c \
			execution/help_mredir/redir_infile2.c \
			execution/help_mredir/redir_outfile2.c \
			lib/data_structures/dynamic_array.c \
			lib/data_structures/dynamic_string.c \
			lib/data_structures/linked_list.c \
			lib/data_structures/linked_list_2.c \
			lib/builtins/env.c \
			lib/builtins/echo.c \
			lib/builtins/export.c \
			lib/builtins/cd.c \
			lib/builtins/pwd.c \
			lib/builtins/unset.c \
			lib/builtins/exit.c \
			lib/utils/help_for_exe2.c/cmd_is_dir.c \
			lib/utils/help_for_exe2.c/check_if_dir.c \
			lib/utils/help_for_exe2.c/cmd_is_exe.c \
			lib/utils/help_for_exe2.c/exe_cmd.c \
			lib/utils/help_for_exe2.c/is_dir2.c \
			lib/utils/help_for_exe2.c/put_error.c \
			lib/utils/gc.c \
			lib/utils/execute_cmd2.c \
			lib/help_fun/print_expo.c \
			lib/help_fun/check_overflow.c \
			lib/help_fun/get_clean_key.c \
			lib/help_fun/get_cpy_of_env.c \
			lib/help_fun/get_value_and_key.c \
			lib/help_fun/sort_arr.c \
			lib/help_fun/valid_key.c \
			lib/help_fun/ch_in_env.c \
			lib/extra_cmd/extra_command.c \
			lib/extra_cmd/help_func2/fond_cmd.c \
			lib/extra_cmd/help_func2/cmd_is_dir.c \
			lib/extra_cmd/help_func2/is_executable.c \
			lib/extra_cmd/help_func2/path_is_set.c \
			lib/extra_cmd/help_func2/valid_path.c \
			lib/extra_cmd/help_func2/wait_process.c \
			lib/extra_cmd/help_func2/is_directory.c \
			lib/extra_cmd/help_func2/get_path_variable.c \
			lib/bootstrap/init.c \
			lib/bootstrap/env_load.c 

include libft_src.mk

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_FILES) 
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(NAME) $(CFLAGS) -L/usr/local/lib -lreadline -lhistory

$(LIBFT): $(LIBFT_OFILES)
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
.SECONDARY: $(OBJ_FILES) $(LIBFT_OFILES)