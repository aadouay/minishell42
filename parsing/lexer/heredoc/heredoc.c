/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:16:23 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 14:49:39 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incoming_eof(char *delimiter, int fd)
{
	char	*trimmed;

	trimmed = ft_strtrim(delimiter, "\n");
	write(2, "warning: heredoc delimited by end-of-file (wanted `", 52);
	write(2, trimmed, ft_strlen(trimmed));
	write(2, "')", 2);
	write(1, "\n", 1);
	close(fd);
	gc_clear();
	exit(0);
}

void	handle_incoming_input(int fd, char *delimiter)
{
	char	*line;
	char	*trimmed;
	bool	should_expand;

	should_expand = check_if_should_expand(delimiter);
	line = NULL;
	while (true)
	{
		line = readline(">");
		if (!line)
			incoming_eof(delimiter, fd);
		trimmed = line;
		if (ft_strcmp(trimmed, ft_strtrim(delimiter, "\"")) == 0
			|| ft_strcmp(trimmed, ft_strtrim(delimiter, "'")) == 0)
			break ;
		if (should_expand)
			line = heredoc_expantion(line);
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
	}
	close(fd);
	gc_clear();
	exit(0);
}

static void	handle_heredoc_core(t_redirs *redirection, int pid, int *status)
{
	g_minishell.from_child = 1;
	if (pid == 0)
	{
		signal(SIGINT, signal_her);
		handle_incoming_input(redirection->fd, redirection->file);
	}
	else
	{
		waitpid(pid, status, 0);
		if (WIFEXITED(*status))
		{
			if (WEXITSTATUS(*status) == 130)
			{
				printf("\n");
				g_minishell.exit_code = 130;
				g_minishell.resev_signal_in_herdoc = 1;
			}
			else
				g_minishell.exit_code = WEXITSTATUS(*status);
		}
		close(redirection->fd);
	}
}

void	handle_heredoc(t_parser *p, t_token *token, t_command *cmd)
{
	t_token		*file_token;
	t_redirs	*redirection;
	int			pid;
	int			status;

	file_token = parser_advance(p);
	redirection = gc_malloc(sizeof(t_redirs));
	redirection->type = get_redir_type(token);
	redirection->file = ft_strdup(file_token->value);
	redirection->heredoc_filename = generate_temp_filename();
	redirection->fd = open(redirection->heredoc_filename,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirection->fd < 0)
		perror("open");
	pid = fork();
	handle_heredoc_core(redirection, pid, &status);
	g_minishell.from_child = 0;
	add_element(cmd->redirs, redirection);
	cmd->redirs_count++;
}
