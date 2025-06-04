/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_and_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:49:02 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:49:03 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_value_and_key(char **key, char **value, char *arg)
{
	char	*equal;
	int		len1;
	int		len2;
	int		target_len;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return ;
	}
	len1 = ft_strlen(arg);
	len2 = ft_strlen(equal);
	target_len = len1 - len2;
	*key = ft_substr(arg, 0, target_len);
	if (value != NULL)
		*value = ft_strdup(equal + 1);
}
