/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:49:41 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:26:09 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspecial(int c)
{
	return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '['
			&& c <= '`') || (c >= '{' && c <= '~'));
}

bool	is_lexer_on(t_lexer *lexer, char c)
{
	return (lexer->input[lexer->pos] == c);
}

bool	check_all_quotes_closed(char *str)
{
	int		i;
	char	state;

	i = 0;
	state = 'N';
	while (str[i])
	{
		if ((state == 'D' && str[i] == '"') || (state == 'S' && str[i] == '\''))
			state = 'N';
		else if (state == 'N')
		{
			if (str[i] == '"')
				state = 'D';
			else if (str[i] == '\'')
				state = 'S';
		}
		i++;
	}
	return (state == 'N');
}

void	show_syntax_error(void)
{
	printf("Syntax error: unclosed quote\n");
	g_minishell.is_closed = false;
}
