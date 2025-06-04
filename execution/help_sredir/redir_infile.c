/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 09:39:46 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 09:39:47 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in_file(t_redir_data *data)
{
	if (data->redir->file[0] == '\0' && data->redir->raw)
	{
		show_ambiguous_redirection_error(data);
		return (1);
	}
	data->fd = open(data->redir->file, O_RDONLY);
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
	dup2(data->fd, STDIN_FILENO);
	close(data->fd);
	return (0);
}
