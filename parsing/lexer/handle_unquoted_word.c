/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unquoted_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:32 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:08:36 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_operator(const char *word, t_lexer *lexer, t_array *tokens)
{
	if (word[0] == '>' && word[1] == '>')
		return (make_add(lexer, tokens, APPEND_OUT, ">>"), 2);
	else if (word[0] == '<' && word[1] == '<')
		return (make_add(lexer, tokens, HERE_DOC, "<<"), 2);
	else if (word[0] == '|' && word[1] != '|')
		return (make_add(lexer, tokens, PIPE, "|"), 1);
	else if (word[0] == '>')
		return (make_add(lexer, tokens, REDIRECT_OUT, ">"), 1);
	else if (word[0] == '<')
		return (make_add(lexer, tokens, REDIRECT_IN, "<"), 1);
	return (0);
}

static char	*handle_when_word_linked_w_op(char *word, t_lexer *lexer,
		t_array *tokens)
{
	int		i;
	char	*before;
	int		op_len;

	i = 0;
	while (word[i])
	{
		if (word[i] == '>' || word[i] == '<' || word[i] == '|')
		{
			if (i > 0)
			{
				before = ft_substr(word, 0, i);
				if (!before)
					return (NULL);
				make_add(lexer, tokens, WORD, before);
			}
			op_len = handle_operator(&word[i], lexer, tokens);
			word = &word[i + op_len];
			i = 0;
		}
		else
			i++;
	}
	return (word);
}

static void	collect_the_word(t_lexer *lexer, bool *in_ds)
{
	while (lexer->input[lexer->pos] && (ft_isalnum(lexer->input[lexer->pos])
			|| ft_isspecial(lexer->input[lexer->pos])
			|| ((*in_ds) && (lexer->input[lexer->pos] == ' '
					|| lexer->input[lexer->pos] == '\t'))))
	{
		if (lexer->input[lexer->pos] == '"' || lexer->input[lexer->pos] == '\'')
			(*in_ds) = true;
		lexer->pos++;
	}
}

void	handle_word(t_lexer *lexer, t_array *tokens)
{
	char	*word;
	size_t	start;
	bool	in_ds;

	in_ds = false;
	start = lexer->pos;
	collect_the_word(lexer, &in_ds);
	word = ft_substr(lexer->input, start, lexer->pos - start);
	if (!word)
		return ;
	if (!check_all_quotes_closed(word))
	{
		printf("Syntax error: unclosed quote\n");
		g_minishell.is_closed = false;
	}
	if (!in_ds)
		word = handle_when_word_linked_w_op(word, lexer, tokens);
	if (word && word[0] != '\0')
		make_add(lexer, tokens, WORD, word);
}
