/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:39:42 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 09:39:43 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_herdoc(t_redir_data *data)
{
	data->fd = open(data->redir->heredoc_filename, O_RDONLY);
	if (data->fd < 0)
	{
		perror(data->redir->file);
		dup2(data->savein, 0);
		dup2(data->saveout, 1);
		close(data->savein);
		close(data->saveout);
		g_minishell.exit_code = 1;
		return (1);
	}
	dup2(data->fd, 0);
	close(data->fd);
	return (0);
}
