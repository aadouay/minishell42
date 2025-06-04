/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_is_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:03 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:47:22 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path_is_set(t_command *cmd, char *path)
{
	if (!path)
	{
		put_error((*(char **)cmd->args->array), ": No such file or directory");
		return (1);
	}
	return (0);
}
