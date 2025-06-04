/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:46:43 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 07:56:42 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dir(const char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

void	check_if_cmd_id_dir(t_command *cmd)
{
	if (is_dir((*(char **)cmd->args->array)))
	{
		if (access((*(char **)cmd->args->array), F_OK) == 0)
		{
			if (is_directory((*(char **)cmd->args->array)) == 1)
			{
				ft_putstr_fd((*(char **)cmd->args->array), 2);
				ft_putendl_fd(": Is a directory", 2);
				gc_clear();
				exit(126);
			}
			ft_putstr_fd((*(char **)cmd->args->array), 2);
			ft_putendl_fd(": Permission denied", 2);
			exit(126);
		}
		else
		{
			ft_putstr_fd((*(char **)cmd->args->array), 2);
			ft_putendl_fd(": No such file or directory", 2);
			gc_clear();
			exit(127);
		}
	}
}
