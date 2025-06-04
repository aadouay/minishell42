/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:43:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/26 14:10:53 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(t_parser *parser, t_array *tokens)
{
	parser->index = 0;
	parser->size = tokens->size;
	parser->tokens = tokens;
}

void	init_pipeline(t_pipeline *pipeline)
{
	t_array	*cmds;

	cmds = gc_malloc(sizeof(t_array));
	if (!cmds)
		return ;
	array_init(cmds, 42, sizeof(t_command));
	pipeline->cmd_count = 0;
	pipeline->cmds = cmds;
}

void	init_command(t_command *cmd)
{
	t_array	*redirs;
	t_array	*args;

	redirs = gc_malloc(sizeof(t_array));
	if (!redirs)
		return ;
	array_init(redirs, 42, sizeof(t_redirs));
	args = gc_malloc(sizeof(t_array));
	if (!args)
	{
		free_array(redirs);
		return ;
	}
	array_init(args, 42, sizeof(char *));
	cmd->args_count = 0;
	cmd->args = args;
	cmd->redirs = redirs;
	cmd->redirs_count = 0;
}
