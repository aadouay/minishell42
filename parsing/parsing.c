/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:46:53 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:11:52 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*parser(char *command)
{
	t_parser	*parser;
	t_array		*tokens;

	if (!command)
		return (NULL);
	parser = gc_malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	tokens = lexer(command);
	if (!tokens || tokens->is_empty)
		return (NULL);
	expander(tokens);
	init_parser(parser, tokens);
	if (!validate_token_grammar(parser))
		return (NULL);
	parser->pipeline = parse_pipeline(parser);
	return (parser);
}
