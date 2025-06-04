/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:49:18 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:49:19 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_msg(char *key)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("'", 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

int	check_key(char *key)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(key[0]) && key[0] != '_') || key[0] == 32)
	{
		print_msg(key);
		return (0);
	}
	while (key[i])
	{
		if (key[i] == '=')
			break ;
		if (key[i] == '+' && key[i + 1] == '=')
			break ;
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			print_msg(key);
			return (0);
		}
		i++;
	}
	return (1);
}
