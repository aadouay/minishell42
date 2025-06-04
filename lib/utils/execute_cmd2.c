/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:06:34 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/02 14:18:08 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	execute_cmd2(t_command *cmd, t_list *env)
{
	t_extcmd	data;

	data.path = get_path_variable(env);
	data.valid_path = NULL;
	data.env_arr = get_copy_of_env(env);
	checke_if_cmd_is_exectable_file2(cmd, &data);
	check_if_cmd_id_dir2(cmd);
	if (check_path_is_set(cmd, data.path))
		(gc_clear(), exit(127));
	execute_cmd_after_parser2(cmd, &data);
}
