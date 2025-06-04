/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:38:20 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 11:51:43 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_args(t_token *token, t_command *cmd)
{
	int		k;
	char	**args;

	args = ft_split(token->value, ' ');
	k = 0;
	while (args[k])
	{
		add_element(cmd->args, &args[k]);
		cmd->args_count++;
		k++;
	}
}

static void	handle_redirection(t_parser *p, t_token *token, t_command *cmd)
{
	t_token		*file_token;
	t_redirs	*redirection;

	file_token = parser_advance(p);
	redirection = gc_malloc(sizeof(t_redirs));
	redirection->type = get_redir_type(token);
	if (file_token->raw)
		redirection->raw = ft_strdup(file_token->raw);
	else
		file_token->raw = NULL;
	redirection->file = ft_strdup(file_token->value);
	add_element(cmd->redirs, redirection);
	cmd->redirs_count++;
}

static	void	parse_command_core(t_parser *p, t_token *token, t_command *cmd)
{
	char		*arg;

	if (is_type(token, WORD) || is_type(token, EXIT_STATUS))
	{
		if (token->value && ft_strlen(token->value) > 1
			&& ft_strchr(token->value, ' ') && token->expandable == true
			&& !token->in_double_quotes)
			split_args(token, cmd);
		else
		{
			if (token->value[0] == '\0' && token->raw != NULL
				&& token->in_double_quotes == false)
				return ;
			arg = ft_strdup(token->value);
			add_element(cmd->args, &arg);
			cmd->args_count++;
		}
	}
	else if (token->type == HERE_DOC
		&& g_minishell.resev_signal_in_herdoc == 0)
		handle_heredoc(p, token, cmd);
	else if (is_redirection(token->type))
		handle_redirection(p, token, cmd);
}

t_command	*parse_command(t_parser *p)
{
	t_command	*cmd;
	t_token		*token;

	cmd = gc_malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	init_command(cmd);
	while (parser_peek(p) && parser_peek(p)->type != PIPE)
	{
		token = parser_advance(p);
		parse_command_core(p, token, cmd);
	}
	((char **)cmd->args->array)[cmd->args_count] = NULL;
	return (cmd);
}

t_pipeline	*parse_pipeline(t_parser *p)
{
	t_pipeline	*pipeline;

	pipeline = gc_malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	init_pipeline(pipeline);
	while (parser_peek(p))
	{
		add_element(pipeline->cmds, parse_command(p));
		pipeline->cmd_count++;
		if (parser_peek(p) && parser_peek(p)->type == PIPE)
			parser_advance(p);
	}
	return (pipeline);
}
