/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cpy_of_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:48:59 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:49:00 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_copy_of_env(t_list *env)
{
	int		len;
	char	**arr;
	int		i;

	len = ft_lstsize(env);
	arr = gc_malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = ft_strdup((char *)env->content);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
