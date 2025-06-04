/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:08 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:47:16 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_process(int status)
{
	if (WTERMSIG(status) == SIGINT)
		printf("\n");
	if (status == 131)
		ft_putendl_fd("Quit (core dumped)", 2);
	if (WIFEXITED(status))
		g_minishell.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_minishell.exit_code = 128 + WTERMSIG(status);
	else
		g_minishell.exit_code = 1;
}
