/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:00 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 16:46:38 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checke_if_cmd_is_exectable_file(t_command *cmd, t_extcmd *data)
{
	if (access((*(char **)cmd->args->array), X_OK) == 0
		&& is_directory((*(char **)cmd->args->array)) == 0)
	{
		data->valid_path = (*(char **)cmd->args->array);
		if (execve(data->valid_path, (char **)cmd->args->array,
				data->env_arr) == -1)
			(perror("execve failed"), gc_clear(), exit(127));
	}
}
