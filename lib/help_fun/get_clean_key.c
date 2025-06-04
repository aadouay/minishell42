/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:48:54 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:48:55 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_clean_key(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			break ;
		if (arg[i] == '=')
			break ;
		i++;
	}
	return (ft_substr(arg, 0, i));
}
