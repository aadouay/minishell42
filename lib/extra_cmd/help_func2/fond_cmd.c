/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fond_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:46:51 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:46:52 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*fond_cmd(char *cmd, char *path)
{
	int		i;
	char	**arr;
	char	*tmp;
	char	*new;

	i = 0;
	arr = ft_split(path, ':');
	if (!path)
		return (NULL);
	tmp = NULL;
	new = NULL;
	while (arr[i])
	{
		tmp = ft_strjoin(arr[i], "/");
		new = ft_strjoin(tmp, cmd);
		if (access(new, X_OK) == 0)
			return (new);
		i++;
	}
	return (NULL);
}
