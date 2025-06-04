/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:52:23 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:25:32 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_temp_filename(void)
{
	static int	count = 0;
	char		*number;
	char		*temp;
	char		*filename;

	number = ft_itoa(count++);
	temp = ft_strjoin("/tmp/heredoc_", number);
	filename = ft_strjoin(temp, ".txt");
	return (filename);
}

void	signal_her(int sig)
{
	(void)sig;
	g_minishell.exit_code = 130;
	g_minishell.resev_signal_in_herdoc = 1;
	exit(130);
}

bool	check_if_should_expand(char *delimiter)
{
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		return (false);
	return (true);
}
