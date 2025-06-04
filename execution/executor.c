/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:16:58 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:48:51 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	static char	*builins[] = {"echo", "cd", "pwd", "export", "unset", "env", \
	"exit"};
	int			i;

	if (!cmd)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_builtins	get_builtin_type(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	else
		return (UNKNOWN);
}

void	handle_builtin(char *cmd_raw, t_command *cmd, t_list **env_list)
{
	t_builtins	type;

	type = get_builtin_type(cmd_raw);
	if (type == UNKNOWN)
		return ;
	if (type == ENV)
		return (env());
	else if (type == EXPORT)
		return (export(cmd));
	else if (type == CD)
		return (cd(cmd));
	else if (type == ECHO)
		return (echo(cmd));
	else if (type == PWD)
		return (pwd());
	else if (type == UNSET)
		remove_variable(env_list, cmd);
	else if (type == EXIT)
		exit_fun(cmd);
}

void	execute_command(t_command *cmd, t_list **env)
{
	char	*cmd_char;

	if (cmd->redirs->is_empty != 1)
		return (redir_for_single_cmd(cmd));
	if (cmd->args_count == 0)
		return ;
	cmd_char = *(char **)get_element(cmd->args, 0);
	if (is_builtin(cmd_char))
		return (handle_builtin(cmd_char, cmd, env));
	external_cmd(cmd, g_minishell.env);
}

void	executor(t_pipeline *pipeline)
{
	t_list		**env;
	int			i;
	t_command	*cmd;

	env = &(g_minishell.env);
	i = 0;
	g_minishell.from_child = 1;
	if (pipeline->cmd_count == 1)
	{
		cmd = (t_command *)get_element(pipeline->cmds, i);
		if (cmd->args_count == 0)
		{
			g_minishell.from_child = 0;
			return ;
		}
		execute_command(cmd, env);
	}
	else
		execute_with_pipe(pipeline, env);
	g_minishell.from_child = 0;
}
