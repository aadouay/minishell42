/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:05 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:47:18 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_path(t_command *cmd, char *path)
{
	if (!path)
	{
		put_error((*(char **)cmd->args->array), ": command not found\n");
		g_minishell.exit_code = 127;
		return (1);
	}
	return (0);
}
