/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:46:07 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 16:14:57 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_after_parser(t_command *cmd, t_extcmd *data)
{
	data->valid_path = fond_cmd((*(char **)cmd->args->array), data->path);
	if (data->valid_path != NULL)
		execve(data->valid_path, ((char **)cmd->args->array), data->env_arr);
	ft_putstr_fd((*(char **)cmd->args->array), 2);
	ft_putendl_fd(": command not found", 2);
	gc_clear();
	exit(127);
}

void	external_cmd(t_command *cmd, t_list *env)
{
	t_extcmd	data;

	data.path = get_path_variable(env);
	data.valid_path = NULL;
	data.env_arr = get_copy_of_env(env);
	data.pid = fork();
	if (data.pid == -1)
	{
		perror("fork failed");
	}
	else if (data.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		checke_if_cmd_is_exectable_file(cmd, &data);
		check_if_cmd_id_dir(cmd);
		if (check_path_is_set(cmd, data.path))
			(gc_clear(), exit(127));
		execute_cmd_after_parser(cmd, &data);
	}
	else
		waitpid(data.pid, &data.status, 0);
	wait_process(data.status);
	return ;
}
