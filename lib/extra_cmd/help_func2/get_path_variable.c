/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_variable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:46:54 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:47:33 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_variable(t_list *env)
{
	t_list	*cpy;

	cpy = env;
	while (cpy)
	{
		if (ft_strncmp((char *)cpy->content, "PATH=", 5) == 0)
			return (ft_strdup((char *)cpy->content + 5));
		cpy = cpy->next;
	}
	return (NULL);
}
