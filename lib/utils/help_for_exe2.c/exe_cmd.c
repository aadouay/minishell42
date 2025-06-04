/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:26:06 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/02 14:15:46 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_after_parser2(t_command *cmd, t_extcmd *data)
{
	data->valid_path = fond_cmd((*(char **)cmd->args->array), data->path);
	if (data->valid_path != NULL)
		execve(data->valid_path, ((char **)cmd->args->array), data->env_arr);
	put_error((*(char **)cmd->args->array), ": command not found");
	gc_clear();
	exit(127);
}
