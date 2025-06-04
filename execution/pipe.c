/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:16:49 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:04:47 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_status_all_cmd(int status)
{
	int	sig;

	if (g_minishell.handle_extra_line == 0)
	{
		if (WIFSIGNALED(status))
		{
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
				{
					if (g_minishell.exit_code != 130)
						write(1, "\n", 1);
				}
			}
			g_minishell.handle_extra_line = 1;
		}
	}
}

void	execute_with_pipe(t_pipeline *pipeline, t_list **env)
{
	t_pipe	data;

	data.i = 1;
	data.cmd = get_element(pipeline->cmds, 0);
	pipe(data.fd);
	execute_first_cmd(data.cmd, env, data.fd);
	close(data.fd[1]);
	data.prev_r_p = data.fd[0];
	execute_middle_cmds(pipeline, env, data.fd, &data.prev_r_p);
	data.cmd = get_element(pipeline->cmds, pipeline->cmd_count - 1);
	execute_last_cmd(data.cmd, env, &data.prev_r_p);
	close(data.prev_r_p);
	while (wait(&data.status) > 0)
	{
		parse_status_all_cmd(data.status);
	}
}
