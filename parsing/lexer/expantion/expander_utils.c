/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:01:19 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 12:34:38 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	getting_env_value(char *line, char **final_value, int *i)
{
	int		j;
	char	*var_name;
	char	*var;

	j = (*i) + 1;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	var_name = ft_substr(line, (*i) + 1, j - (*i) - 1);
	var = get_env_value(var_name);
	if (var)
		*final_value = dynamic_str_append_str(*final_value, var);
	(*i) = j;
}

static void	handling_exit_status(char **final_value, int *i)
{
	*final_value = dynamic_str_append_str(*final_value,
			ft_itoa(g_minishell.exit_code));
	(*i) += 2;
}

void	expantion_core(char *line, char **final_value, int *i)
{
	if (line[(*i) + 1] == '?')
		handling_exit_status(final_value, i);
	else if (line[(*i) + 1] && ft_isdigit(line[(*i) + 1]))
		(*i) += 2;
	else if (line[(*i) + 1] && (ft_isalpha(line[(*i) + 1]) || line[(*i)
				+ 1] == '_'))
		getting_env_value(line, final_value, i);
	else
	{
		*final_value = dynamic_str_append_char(*final_value, '$');
		(*i)++;
	}
}

void	set_data_handle_word(t_handle_word_expantion *data,
		t_expander *expander)
{
	data->i = 0;
	data->in_single = false;
	data->in_double = false;
	data->current_token = expander->current_token;
	data->final_value = make_dynamic_str();
	data->raw_value = data->current_token->value;
}
