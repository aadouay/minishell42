/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:16 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 13:34:53 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_end_of_file(int *fd)
{
	int		i;
	char	*buffer[2000];

	i = read(*fd, buffer, 2000);
	while (i)
	{
		i = read(*fd, buffer, 2000);
	}
}
