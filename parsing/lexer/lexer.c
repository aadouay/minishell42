/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:49:53 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:25:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_linked_token(t_lexer *lexer, t_array *tokens)
{
	if (lexer->input[lexer->pos] == '<')
	{
		if (lexer->input[lexer->pos + 1] == '<')
			make_add_move(lexer, tokens, HERE_DOC, "<<");
		else
			make_add(lexer, tokens, REDIRECT_IN, "<");
	}
	else if (lexer->input[lexer->pos] == '>')
	{
		if (lexer->input[lexer->pos + 1] == '>')
			make_add_move(lexer, tokens, APPEND_OUT, ">>");
		else
			make_add(lexer, tokens, REDIRECT_OUT, ">");
	}
	else if (lexer->input[lexer->pos] == '|')
		make_add(lexer, tokens, PIPE, "|");
}

static	void	collect_word(t_lexer *lexer,
	char *starting_qoute, bool *has_token_linked)
{
	bool	on_qoute;

	on_qoute = false;
	while (lexer->input[lexer->pos])
	{
		if (on_qoute == false && (is_lexer_on(lexer, ' ') || is_lexer_on(lexer,
					'|') || is_lexer_on(lexer, '>') || is_lexer_on(lexer, '<')))
		{
			*has_token_linked = true;
			break ;
		}
		if (is_lexer_on(lexer, '"') || is_lexer_on(lexer, '\''))
		{
			if (!on_qoute)
				*starting_qoute = lexer->input[lexer->pos];
			if (*starting_qoute == lexer->input[lexer->pos])
				on_qoute = !on_qoute;
		}
		lexer->pos++;
	}
}

static void	handle_string_on_quote(t_lexer *lexer, t_array *tokens)
{
	char	*word;
	size_t	start;
	bool	has_token_linked;
	char	*starting_qoute;

	has_token_linked = false;
	start = lexer->pos;
	starting_qoute = gc_malloc(sizeof(char));
	if (!starting_qoute)
		return ;
	collect_word(lexer, starting_qoute, &has_token_linked);
	word = ft_substr(lexer->input, start, lexer->pos - start);
	if (!word)
		return ;
	if (!check_all_quotes_closed(word))
		return (show_syntax_error());
	if (word && word[0] != '\0')
		make_add(lexer, tokens, WORD, word);
	else
		make_add(lexer, tokens, WORD, "");
	if (has_token_linked)
		handle_linked_token(lexer, tokens);
}

void	lexer_core(t_array *tokens, t_lexer *lexer)
{
	if (lexer->input[lexer->pos] == '|')
		handle_pipe_and_or_op(lexer, tokens);
	else if (lexer->input[lexer->pos] == '<')
		handle_rin_doc(lexer, tokens);
	else if (lexer->input[lexer->pos] == '>')
		handle_rout_append(lexer, tokens);
	else if (lexer->input[lexer->pos] == '&' && lexer->input[lexer->pos
			+ 1] == '&')
		handle_and_op(lexer, tokens);
	else if (lexer->input[lexer->pos] == '$' && lexer->input[lexer->pos
			+ 1] == '?' && (lexer->input[lexer->pos + 1]
			&& lexer->input[lexer->pos
				+ 1] == ' '))
		handle_exit_status(lexer, tokens);
	else if (lexer->input[lexer->pos] == '"'
		|| lexer->input[lexer->pos] == '\'')
		handle_string_on_quote(lexer, tokens);
	else if (ft_isalnum(lexer->input[lexer->pos])
		|| ft_isspecial(lexer->input[lexer->pos]))
		handle_word(lexer, tokens);
}

t_array	*lexer(char *input)
{
	t_array	*tokens;
	t_lexer	lexer;

	if (!input)
		return (NULL);
	ft_memset(&lexer, 0, sizeof(lexer));
	init_lexer(&lexer, input);
	tokens = gc_malloc(sizeof(t_array));
	array_init(tokens, 42, sizeof(t_token));
	lexer.pos = 0;
	while (lexer.input[lexer.pos])
	{
		while ((lexer.input[lexer.pos] == ' '
				|| lexer.input[lexer.pos] == '\t'))
			lexer.pos++;
		if (!lexer.input[lexer.pos])
			break ;
		lexer_core(tokens, &lexer);
		if (lexer.pos < lexer.len_input)
			lexer.pos++;
		else
			break ;
	}
	return (tokens);
}
