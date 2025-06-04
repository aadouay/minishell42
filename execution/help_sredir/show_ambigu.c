/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_ambigu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:39:56 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 09:39:57 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_ambiguous_redirection_error(t_redir_data *data)
{
	ft_putstr_fd(data->redir->raw, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	dup2(data->savein, 0);
	dup2(data->saveout, 1);
	close(data->savein);
	close(data->saveout);
	g_minishell.exit_code = 1;
}
