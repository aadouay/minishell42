/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:15:36 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/29 14:17:23 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_element(t_list **env, char *arg)
{
	t_exporta	data;
	t_list		*current;
	t_list		*previous;

	previous = 0;
	current = *env;
	while (current)
	{
		get_value_and_key(&data.key_list, &data.value_list, current->content);
		if (ft_strcmp(arg, data.key_list) == 0)
		{
			if (previous == 0)
				*env = current->next;
			else
				previous->next = current->next;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	remove_variable(t_list **env, t_command *cmd)
{
	int		i;
	char	**args;

	i = 1;
	args = ((char **)cmd->args->array);
	while (args[i])
	{
		remove_element(env, args[i]);
		i++;
	}
	g_minishell.exit_code = 0;
}
