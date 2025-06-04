/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:30:06 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/28 13:09:12 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_type(t_token *token, t_token_type kind)
{
	return (token->type == kind);
}

t_token	*make_token(t_token_type token_type, char *value)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->value = ft_strdup(value);
	token->raw = NULL;
	token->expandable = false;
	token->in_double_quotes = false;
	token->in_single_quotes = false;
	return (token);
}

void	make_add(t_lexer *lexer, t_array *tokens, t_token_type type,
		char *value)
{
	t_token	*token;

	token = make_token(type, value);
	add_element(tokens, token);
	lexer->index++;
}

void	make_add_move(t_lexer *lexer, t_array *tokens, t_token_type type,
		char *value)
{
	t_token	*token;

	token = make_token(type, value);
	add_element(tokens, token);
	lexer->index++;
	lexer->pos++;
}

char	get_redir_type(t_token *token)
{
	if (is_type(token, REDIRECT_IN) || is_type(token, REDIRECT_OUT))
		return (token->value[0]);
	else if (is_type(token, APPEND_OUT))
		return ('a');
	else if (is_type(token, HERE_DOC))
		return ('h');
	else
		return ('x');
}
