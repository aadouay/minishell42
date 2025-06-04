/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:17:51 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/06 23:28:36 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_and_op(t_lexer *lexer, t_array *tokens)
{
	make_add_move(lexer, tokens, AND_OPERATOR, "&&");
}

void	handle_pipe_and_or_op(t_lexer *lexer, t_array *tokens)
{
	if (lexer->input[lexer->pos + 1] == '|')
		make_add_move(lexer, tokens, OR_OPERATOR, "||");
	else
		make_add(lexer, tokens, PIPE, "|");
}

void	handle_rin_doc(t_lexer *lexer, t_array *tokens)
{
	if (lexer->input[lexer->pos + 1] == '<')
		make_add_move(lexer, tokens, HERE_DOC, "<<");
	else
		make_add(lexer, tokens, REDIRECT_IN, "<");
}

void	handle_rout_append(t_lexer *lexer, t_array *tokens)
{
	if (lexer->input[lexer->pos + 1] == '>')
		make_add_move(lexer, tokens, APPEND_OUT, ">>");
	else
		make_add(lexer, tokens, REDIRECT_OUT, ">");
}

void	handle_exit_status(t_lexer *lexer, t_array *tokens)
{
	make_add_move(lexer, tokens, EXIT_STATUS, "$?");
}
