/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:39:19 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/29 08:28:11 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(void)
{
	char	*equal;
	t_list	*env;

	env = g_minishell.env;
	while (env != NULL)
	{
		equal = ft_strchr((char *)env->content, '=');
		if (equal)
		{
			printf("%s", (char *)env->content);
			printf("\n");
		}
		env = env->next;
	}
	g_minishell.exit_code = 0;
}

char	*get_env_value(const char *key)
{
	size_t	len;
	t_list	*env_list;
	char	*content;

	len = ft_strlen(key);
	env_list = g_minishell.env;
	while (env_list)
	{
		content = (char *)env_list->content;
		if (ft_strncmp(content, key, len) == 0 && content[len] == '=')
		{
			return (content + len + 1);
		}
		env_list = env_list->next;
	}
	return (NULL);
}
