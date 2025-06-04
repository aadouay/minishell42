/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:28:36 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:13:55 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_var(t_list *env, char *arg)
{
	t_exporta	data;

	data.cpy_node = ft_lstnew((void *)ft_strdup(arg));
	ft_lstadd_back(&env, data.cpy_node);
}

static void	check_extra_case(t_exporta *data, char *arg)
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
		data->cpy->content = (void *)ft_strdup(arg);
}

static void	update_or_add_to_env(t_list *env, char *arg)
{
	t_exporta	data;

	data.cpy = env;
	get_value_and_key(&data.key_arg, &data.value_arg, arg);
	while (data.cpy != NULL)
	{
		get_value_and_key(&data.key_list, &data.value_list, data.cpy->content);
		if (ft_strcmp(data.key_arg, data.key_list) == 0)
		{
			check_extra_case(&data, arg);
			return ;
		}
		data.cpy = data.cpy->next;
	}
	new_var(env, arg);
}

void	check_errors(int check)
{
	if (check == 1)
		g_minishell.exit_code = 1;
	else
		g_minishell.exit_code = 0;
}

void	export(t_command *cmd)
{
	t_exporta	data;

	data.i = 0;
	data.check_error = 0;
	if (cmd->args_count == 1)
		return (print_env(g_minishell.env));
	while (((char **)cmd->args->array)[data.i])
	{
		data.key = *(char **)get_element(cmd->args, data.i);
		data.is_valid = check_key(data.key);
		if (data.is_valid)
			update_or_add_to_env(g_minishell.env,
				((char **)cmd->args->array)[data.i]);
		else
			data.check_error = 1;
		data.i++;
	}
	check_errors(data.check_error);
	return ;
}
