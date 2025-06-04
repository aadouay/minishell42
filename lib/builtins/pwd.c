/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:14:42 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 17:21:47 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*wcd;

	wcd = getcwd(NULL, 0);
	if (!wcd)
	{
		perror("getcwd is filed!");
		g_minishell.exit_code = 1;
		return ;
	}
	ft_putendl_fd(wcd, 1);
	g_minishell.exit_code = 0;
	free(wcd);
}
