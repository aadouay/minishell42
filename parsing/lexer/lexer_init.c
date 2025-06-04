/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:18:47 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/28 17:55:26 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->index = 0;
	lexer->pos = 0;
	lexer->len_input = ft_strlen(input);
}
