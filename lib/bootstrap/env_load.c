/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:58:29 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/26 09:00:41 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_spicial_env(t_list **env_list)
{
	char	*pwd;
	char	*joined;
	t_list	*shelvl;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd is filed!");
		return ;
	}
	joined = ft_strjoin("PWD=", pwd);
	*env_list = ft_lstnew((void *)joined);
	shelvl = ft_lstnew("SHLVL=1");
	ft_lstadd_back(env_list, shelvl);
	free(pwd);
}

t_list	*create_list_env(char **env)
{
	int		i;
	t_list	*env_list;
	t_list	*next_nod;

	i = 0;
	env_list = NULL;
	next_nod = NULL;
	if (env[i] != NULL)
	{
		while (env[i])
		{
			if (!env_list)
				env_list = ft_lstnew(ft_strdup(env[i]));
			else
			{
				next_nod = ft_lstnew(ft_strdup(env[i]));
				ft_lstadd_back(&env_list, next_nod);
			}
			i++;
		}
	}
	else
		create_spicial_env(&env_list);
	return (env_list);
}
