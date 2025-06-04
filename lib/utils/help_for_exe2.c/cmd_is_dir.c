/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:22:04 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/02 14:17:03 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_cmd_id_dir2(t_command *cmd)
{
	if (is_dir2((*(char **)cmd->args->array)))
	{
		if (access((*(char **)cmd->args->array), F_OK) == 0)
		{
			if (is_directory2((*(char **)cmd->args->array)) == 1)
			{
				put_error((*(char **)cmd->args->array), ": Is a directory");
				exit(126);
			}
			put_error((*(char **)cmd->args->array), ": Permission denied");
			gc_clear();
			exit(126);
		}
		else
		{
			put_error((*(char **)cmd->args->array),
				": No such file or directory");
			gc_clear();
			exit(127);
		}
	}
}
