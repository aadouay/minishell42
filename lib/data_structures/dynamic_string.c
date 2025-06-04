/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:17:28 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:44:00 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"

char	*make_dynamic_str(void)
{
	char	*str;

	str = gc_malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*dynamic_str_append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = gc_malloc((len + 2) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*dynamic_str_append_str(char *str, char *s_append)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	len1 = ft_strlen(str);
	len2 = ft_strlen(s_append);
	new_str = gc_malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, len1 + 1);
	ft_strlcat(new_str, s_append, len1 + len2 + 1);
	return (new_str);
}
