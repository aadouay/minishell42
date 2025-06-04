/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_last_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:49:30 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 13:54:33 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_status_last_cmd(int stat)
{
	int	sig;

	if (WIFEXITED(stat))
		g_minishell.exit_code = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
	{
		if (WIFSIGNALED(stat))
		{
			sig = WTERMSIG(stat);
			if (sig == SIGINT)
			{
				g_minishell.exit_code = 130;
				write(1, "\n", 1);
			}
			else if (sig == SIGQUIT)
			{
				ft_putendl_fd("Quit (core dumped)", 2);
				g_minishell.exit_code = 131;
			}
		}
	}
}

void	execute_last_cmd(t_command *cmd, t_list **env, int *prev_r_p)
{
	int	pid;
	int	stat;

	if (cmd->args_count == 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(*prev_r_p, 0);
		close(*prev_r_p);
		if (cmd->redirs->is_empty != 1)
			return (redir_for_multi_cmds(cmd), gc_clear(),
				exit(g_minishell.exit_code));
		if (is_builtin((*(char **)cmd->args->array)))
			return (handle_builtin((*(char **)cmd->args->array), cmd, env),
				gc_clear(), exit(g_minishell.exit_code));
		execute_cmd2(cmd, *env);
	}
	waitpid(pid, &stat, 0);
	parse_status_last_cmd(stat);
}
