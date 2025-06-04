/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_first.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:35:32 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 13:35:48 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_first_cmd(t_command *cmd, t_list **env, int *fd)
{
	int	pid;

	if (cmd->args_count == 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		if (cmd->redirs->is_empty != 1)
			return (redir_for_multi_cmds(cmd), gc_clear(),
				exit(g_minishell.exit_code));
		if (is_builtin((*(char **)cmd->args->array)))
		{
			handle_builtin((*(char **)cmd->args->array), cmd, env);
			gc_clear();
			exit(g_minishell.exit_code);
		}
		execute_cmd2(cmd, *env);
	}
}
