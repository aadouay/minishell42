/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:38:32 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:48:15 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "data_structure.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND_OUT,
	HERE_DOC,
	ENV_VAR,
	AND_OPERATOR,
	OR_OPERATOR,
	EXIT_STATUS,
}					t_token_type;

typedef enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	UNKNOWN
}					t_builtins;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*raw;
	bool			expandable;
	bool			in_double_quotes;
	bool			in_single_quotes;
}					t_token;

typedef struct s_handle_word_expantion
{
	int				i;
	t_token			*current_token;
	bool			in_single;
	bool			in_double;
	char			*final_value;
	char			*raw_value;
}					t_handle_word_expantion;

typedef struct s_heredoc
{
	char			*heredoc_file;
	int				heredoc_fd;
}					t_heredoc;

typedef struct s_lexer
{
	char			*input;
	int				len_input;
	int				pos;
	int				index;
}					t_lexer;

typedef struct s_expander
{
	t_array			*tokens;
	t_token			*current_token;
	int				expanded_count;
	int				index;
}					t_expander;

typedef struct s_redirs
{
	char			type;
	char			*file;
	char			*heredoc_filename;
	char			*raw;
	int				fd;
}					t_redirs;

typedef struct s_command
{
	t_array			*args;
	int				args_count;
	t_array			*redirs;
	int				redirs_count;
}					t_command;

typedef struct s_pipeline
{
	t_array			*cmds;
	int				cmd_count;
}					t_pipeline;

typedef struct s_parser
{
	t_array			*tokens;
	t_pipeline		*pipeline;
	int				index;
	int				size;
}					t_parser;

typedef struct s_executor
{
	int				exit_status;
	t_list			*envp;
}					t_executor;

typedef struct s_minishell
{
	t_parser		*parser;
	t_list			*env;
	t_gc			gc;
	bool			is_closed;
	int				exit_code;
	int				from_child;
	int				handle_extra_line;
	int				resev_signal_in_herdoc;
	t_heredoc		*heredoc;
}					t_minishell;

extern t_minishell	g_minishell;
bool				check_if_should_expand(char *delimiter);
char				*heredoc_expantion(char *line);
void				handle_heredoc(t_parser *p, t_token *token, t_command *cmd);
void				init_lexer(t_lexer *lexer, char *input);
void				handle_and_op(t_lexer *lexer, t_array *tokens);
void				handle_pipe_and_or_op(t_lexer *lexer, t_array *tokens);
void				handle_rin_doc(t_lexer *lexer, t_array *tokens);
void				handle_rout_append(t_lexer *lexer, t_array *tokens);
void				handle_exit_status(t_lexer *lexer, t_array *tokens);
t_parser			*parser(char *command);
t_array				*lexer(char *input);
bool				is_lexer_on(t_lexer *lexer, char c);
bool				check_all_quotes_closed(char *str);
int					ft_isspecial(int c);
void				handle_word(t_lexer *lexer, t_array *tokens);
char				*generate_temp_filename(void);
void				handle_incoming_input(int fd, char *delimiter);
bool				is_type(t_token *token, t_token_type kind);
t_token				*make_token(t_token_type token_type, char *value);
void				make_add(t_lexer *lexer, t_array *tokens, t_token_type type,
						char *value);
void				make_add_move(t_lexer *lexer, t_array *tokens,
						t_token_type type, char *value);
char				get_redir_type(t_token *token);
t_token				*parser_peek(t_parser *parser);
t_token				*parser_advance(t_parser *parser);
bool				is_redirection(t_token_type type);
t_command			*parse_command(t_parser *p);
t_pipeline			*parse_pipeline(t_parser *p);
void				init_parser(t_parser *parser, t_array *tokens);
void				init_pipeline(t_pipeline *pipeline);
void				init_command(t_command *cmd);
t_list				*create_list_env(char **env);
bool				validate_token_grammar(t_parser *parser);
void				expantion_core(char *line, char **final_value, int *i);
void				set_data_handle_word(t_handle_word_expantion *data,
						t_expander *expander);
void				env(void);
void				cd(t_command *cmd);
void				echo(t_command *cmd);
void				export(t_command *cmd);
void				pwd(void);
void				executor(t_pipeline *parser);
void				expander(t_array *tokens);
char				*get_env_value(const char *key);
void				show_syntax_error(void);

typedef struct s_export_data
{
	t_list			*cpy;
	char			*key_arg;
	char			*value_arg;
	char			*key_list;
	char			*value_list;
	t_list			*cpy_node;
	char			**cpy_list;
	char			*equal;
	int				i;
	int				is_valid;
	int				check_error;
	char			*key;
	int				is_append;
}					t_exporta;

typedef struct s_extern_cmds
{
	char			*path;
	char			*valid_path;
	char			**env_arr;
	pid_t			pid;
	int				status;
}					t_extcmd;

typedef struct s_redir
{
	int				i;
	t_list			**env;
	int				fd;
	int				savein;
	int				saveout;
	t_redirs		*redir;

}					t_redir_data;

typedef struct s_pipe
{
	int				fd[2];
	int				prev_r_p;
	int				i;
	pid_t			pid;
	t_command		*cmd;
	int				status;
}					t_pipe;

void				handle_sigint(int sig);
int					check_overflow(const char *nptr);
void				print_env(t_list *env);
char				*get_clean_key(char *arg);
void				get_value_and_key(char **key, char **value, char *arg);
char				**get_copy_of_env(t_list *env);
void				sort_array(char **arr);
int					check_key(char *key);
void				remove_variable(t_list **env, t_command *cmd);
void				ch_in_env(char *key, char *value);
void				external_cmd(t_command *cmd, t_list *env);
char				*get_path_variable(t_list *env);
void				*fond_cmd(char *cmd, char *path);
void				execute_command(t_command *cmd, t_list **env);
void				execute_with_pipe(t_pipeline *pipeline, t_list **env);
void				execute_cmd2(t_command *cmd, t_list *env);
int					is_builtin(char *cmd);
void				handle_builtin(char *cmd_raw, t_command *cmd,
						t_list **env_list);
void				redir_for_single_cmd(t_command *cmd);
void				redir_for_multi_cmds(t_command *cmd);
void				exit_fun(t_command *cmd);
void				put_error(char *str, char *error);
void				setup_parent_signals(void);
void				checke_if_cmd_is_exectable_file(t_command *cmd,
						t_extcmd *data);
void				check_if_cmd_id_dir(t_command *cmd);
void				wait_process(int status);
int					check_valid_path(t_command *cmd, char *path);
int					check_path_is_set(t_command *cmd, char *path);
int					is_directory(const char *path);
void				checke_if_cmd_is_exectable_file2(t_command *cmd,
						t_extcmd *data);
void				check_if_cmd_id_dir2(t_command *cmd);
void				put_error(char *str, char *error);
int					is_dir2(const char *cmd);
void				execute_cmd_after_parser2(t_command *cmd, t_extcmd *data);
int					is_directory2(const char *path);
void				signal_her(int sig);
int					redir_appand(t_redir_data *data);
int					redir_herdoc(t_redir_data *data);
int					redir_in_file(t_redir_data *data);
int					redir_out_file(t_redir_data *data);
void				show_ambiguous_redirection_error(t_redir_data *data);
int					redir_in_file2(t_redir_data *data);
int					redir_out_file2(t_redir_data *data);
int					redir_appand2(t_redir_data *data);
int					redir_herdoc2(t_redir_data *data);
void				show_ambiguous_redirection_error2(t_redir_data *data);
void				execute_first_cmd(t_command *cmd, t_list **env, int *fd);
void				execute_middle_cmds(t_pipeline *pipeline, t_list **env,
						int *fd, int *prev_r_p);
void				execute_last_cmd(t_command *cmd, t_list **env,
						int *prev_r_p);
void				set_end_of_file(int *fd);

#endif