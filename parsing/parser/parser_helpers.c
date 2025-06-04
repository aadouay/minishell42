/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:03:27 by zbakour           #+#    #+#             */
/*   Updated: 2025/04/17 18:16:40 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parser_peek(t_parser *parser)
{
	if (parser->index < parser->size)
		return (get_element(parser->tokens, parser->index));
	return (NULL);
}

t_token	*parser_advance(t_parser *parser)
{
	if (parser->index < parser->size)
		return (get_element(parser->tokens, parser->index++));
	return (NULL);
}

bool	is_redirection(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT || type == HERE_DOC
		|| type == APPEND_OUT);
}
