/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_for_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:17:11 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 08:52:22 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_data(t_redir_data *data)
{
	data->i = 0;
	data->env = &g_minishell.env;
	data->savein = dup(0);
	data->saveout = dup(1);
}

void	exe_cmd(t_command *cmd, t_redir_data *data)
{
	if (is_builtin((*(char **)cmd->args->array)))
		handle_builtin((*(char **)cmd->args->array), cmd, data->env);
	else
		external_cmd(cmd, *data->env);
	dup2(data->savein, 0);
	dup2(data->saveout, 1);
	close(data->savein);
	close(data->saveout);
}

void	redir_for_single_cmd(t_command *cmd)
{
	t_redir_data	data;

	set_data(&data);
	while (data.i < cmd->redirs_count)
	{
		data.redir = (t_redirs *)get_element(cmd->redirs, data.i);
		if (data.redir->type == '<' && redir_in_file(&data) == 1)
			return ;
		else if (data.redir->type == '>' && redir_out_file(&data) == 1)
			return ;
		else if (data.redir->type == 'a' && redir_appand(&data) == 1)
			return ;
		else if (data.redir->type == 'h' && redir_herdoc(&data) == 1)
			return ;
		data.i++;
	}
	exe_cmd(cmd, &data);
	return ;
}
