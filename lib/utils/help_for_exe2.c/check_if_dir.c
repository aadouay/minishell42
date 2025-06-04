/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:53:39 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 16:05:54 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory2(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
