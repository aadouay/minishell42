/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expantion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:46:59 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 11:47:33 by zbakour          ###   ########.fr       */
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

static void	heredoc_expantion_core(char *line, char **final_value, int *i)
{
	if (line[(*i) + 1] == '?')
		handling_exit_status(final_value, i);
	else if (line[(*i) + 1] && ft_isdigit(line[(*i) + 1]))
		(*i) += 2;
	else if (line[(*i) + 1] && (ft_isalpha(line[(*i) + 1])
			|| line[(*i) + 1] == '_'))
		getting_env_value(line, final_value, i);
	else
	{
		*final_value = dynamic_str_append_char(*final_value, '$');
		(*i)++;
	}
}

char	*heredoc_expantion(char *line)
{
	int		i;
	char	*final_value;

	i = 0;
	final_value = make_dynamic_str();
	while (line[i])
	{
		if (line[i] == '$')
		{
			heredoc_expantion_core(line, &final_value, &i);
			continue ;
		}
		final_value = dynamic_str_append_char(final_value, line[i]);
		i++;
	}
	return (final_value);
}
