/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_middle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:46:19 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 16:29:19 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_for_middle_cmds(int *prev_r_p, int *fd, t_command *cmd,
		t_list **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup2(*prev_r_p, 0);
	close(*prev_r_p);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	if (cmd->redirs->is_empty != 1)
		return (redir_for_multi_cmds(cmd), gc_clear(),
			exit(g_minishell.exit_code));
	if (is_builtin((*(char **)cmd->args->array)))
		return (handle_builtin((*(char **)cmd->args->array), cmd, env),
			gc_clear(), exit(g_minishell.exit_code));
	execute_cmd2(cmd, *env);
}

void	execute_middle_cmds(t_pipeline *pipeline, t_list **env, int *fd,
		int *prev_r_p)
{
	t_command	*cmd;

	int (pid), (i);
	i = 1;
	while (i < pipeline->cmd_count - 1)
	{
		cmd = get_element(pipeline->cmds, i);
		if (cmd->args_count == 0)
		{
			set_end_of_file(prev_r_p);
			i++;
			continue ;
		}
		pipe(fd);
		pid = fork();
		if (pid == 0)
			redir_for_middle_cmds(prev_r_p, fd, cmd, env);
		close(*prev_r_p);
		close(fd[1]);
		*prev_r_p = fd[0];
		i++;
	}
}
