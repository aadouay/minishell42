/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:44:52 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:12:15 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_expander(t_expander *expander, t_array *tokens)
{
	expander->tokens = tokens;
	expander->expanded_count = 0;
	expander->index = 0;
	expander->current_token = get_element(expander->tokens, expander->index);
}

int	single_and_double_flag(t_handle_word_expantion *data)
{
	if (data->current_token->value[data->i] == '\'' && !data->in_double)
	{
		data->in_single = !data->in_single;
		data->i++;
		return (1);
	}
	else if (data->current_token->value[data->i] == '"' && !data->in_single)
	{
		data->in_double = !data->in_double;
		data->i++;
		return (1);
	}
	return (0);
}

static void	handle_word_expantion(t_expander *expander)
{
	t_handle_word_expantion	data;

	set_data_handle_word(&data, expander);
	while (data.current_token->value[data.i])
	{
		if (single_and_double_flag(&data))
			continue ;
		if (data.current_token->value[data.i] == '$' && !data.in_single)
		{
			expantion_core(data.current_token->value, &data.final_value,
				&data.i);
			data.current_token->in_double_quotes = data.in_double;
			data.current_token->in_single_quotes = data.in_single;
			data.current_token->expandable = true;
			expander->expanded_count++;
			continue ;
		}
		data.final_value = dynamic_str_append_char(data.final_value,
				data.current_token->value[data.i]);
		data.i++;
	}
	if (data.current_token->expandable)
		data.current_token->raw = ft_strdup(data.raw_value);
	expander->current_token->value = data.final_value;
}

static void	expander_core(t_expander *expander)
{
	t_token	*pre_token;
	bool	pretoken_is_heredoc;

	pretoken_is_heredoc = false;
	if (!expander->tokens->is_empty && expander->tokens->size > 1
		&& expander->index > 0)
	{
		pre_token = get_element(expander->tokens, expander->index - 1);
		if (pre_token)
			pretoken_is_heredoc = (pre_token->type == HERE_DOC);
	}
	if (!pretoken_is_heredoc && expander->current_token->type == WORD)
		handle_word_expantion(expander);
	else if (!pretoken_is_heredoc
		&& expander->current_token->type == EXIT_STATUS)
		expander->current_token->value = ft_itoa(g_minishell.exit_code);
	expander->index++;
	expander->current_token = get_element(expander->tokens, expander->index);
}

void	expander(t_array *tokens)
{
	t_expander	*expander;

	if (tokens->size == 0)
		return ;
	expander = gc_malloc(sizeof(t_expander));
	if (!expander)
		return ;
	init_expander(expander, tokens);
	while ((size_t)expander->index < expander->tokens->size)
		expander_core(expander);
}
