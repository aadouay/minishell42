/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_in_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:48:06 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:51:20 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_variable(t_list *env, char *arg)
{
	t_exporta	data;

	data.cpy_node = ft_lstnew((void *)ft_strdup(arg));
	ft_lstadd_back(&env, data.cpy_node);
}

static void	check_extra(t_exporta *data, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		i++;
	}
	if (arg[i] == '=')
	{
		data->cpy->content = (void *)ft_strdup(arg);
	}
}

static void	update_env(t_list *env, char *arg)
{
	t_exporta	data;

	data.cpy = env;
	get_value_and_key(&data.key_arg, &data.value_arg, arg);
	while (data.cpy != NULL)
	{
		get_value_and_key(&data.key_list, &data.value_list, data.cpy->content);
		if (ft_strcmp(data.key_arg, data.key_list) == 0)
		{
			check_extra(&data, arg);
			return ;
		}
		data.cpy = data.cpy->next;
	}
	new_variable(env, arg);
}

void	ch_in_env(char *key, char *value)
{
	t_list	*env;
	char	*tmp;
	char	*complet_var;

	env = g_minishell.env;
	tmp = ft_strjoin(key, "=");
	complet_var = ft_strjoin(tmp, value);
	update_env(env, complet_var);
}
