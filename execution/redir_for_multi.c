/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_for_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:24:31 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 10:24:49 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_cmd2(t_command *cmd, t_redir_data *data)
{
	if (is_builtin((*(char **)cmd->args->array)))
		handle_builtin((*(char **)cmd->args->array), cmd, data->env);
	else
		execute_cmd2(cmd, *data->env);
	dup2(data->savein, 0);
	dup2(data->saveout, 1);
	close(data->savein);
	close(data->saveout);
}

void	set_data2(t_redir_data *data)
{
	data->i = 0;
	data->env = &g_minishell.env;
	data->savein = dup(0);
	data->saveout = dup(1);
}

void	redir_for_multi_cmds(t_command *cmd)
{
	t_redir_data	data;

	set_data2(&data);
	while (data.i < cmd->redirs_count)
	{
		data.redir = (t_redirs *)get_element(cmd->redirs, data.i);
		if (data.redir->type == '<' && redir_in_file2(&data) == 1)
			return ;
		else if (data.redir->type == '>' && redir_out_file2(&data) == 1)
			return ;
		else if (data.redir->type == 'a' && redir_appand2(&data) == 1)
			return ;
		else if (data.redir->type == 'h' && redir_herdoc2(&data) == 1)
			return ;
		data.i++;
	}
	exe_cmd2(cmd, &data);
	return ;
}
