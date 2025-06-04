/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:49:44 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/02 20:45:52 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_pipe_syntax(t_parser *parser, int i, t_token *token)
{
	t_token	*next;

	if (!is_type(token, PIPE))
		return (true);
	if (i == 0 || i == parser->size - 1)
	{
		printf("syntax error near unexpected token `|`\n");
		return (false);
	}
	next = get_element(parser->tokens, i + 1);
	if (is_type(next, PIPE))
	{
		printf("syntax error near unexpected token `|`\n");
		return (false);
	}
	return (true);
}

static bool	check_logical_operators(t_token *token)
{
	if (is_type(token, AND_OPERATOR) || is_type(token, OR_OPERATOR))
	{
		printf("syntax error near unexpected token `%s`\n", token->value);
		return (false);
	}
	return (true);
}

bool	word_count(char *str)
{
	int	i;
	int	toggle;
	int	count;

	toggle = 1;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\t' || str[i] == ' ')
		{
			toggle = 1;
		}
		else if (str[i] != '\n' && str[i] != '\t' && str[i] != ' ' && toggle)
		{
			count++;
			if (count > 1)
				return (false);
			toggle = 0;
		}
		i++;
	}
	return (true);
}

static bool	check_redirection_syntax(t_parser *parser, int i, t_token *token)
{
	t_token	*next_token;

	next_token = get_element(parser->tokens, i + 1);
	if (is_redirection(token->type) && (i == parser->size - 1
			|| !is_type(next_token, WORD)))
	{
		printf("syntax error near unexpected token `newline`\n");
		return (false);
	}
	return (true);
}

bool	validate_token_grammar(t_parser *parser)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < parser->size)
	{
		token = get_element(parser->tokens, i);
		if (!check_pipe_syntax(parser, i, token))
			return (false);
		if (!check_logical_operators(token))
			return (false);
		if (!check_redirection_syntax(parser, i, token))
			return (false);
		i++;
	}
	return (true);
}
