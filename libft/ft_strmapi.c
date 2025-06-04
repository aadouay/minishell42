/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:37:31 by zbakour           #+#    #+#             */
/*   Updated: 2025/04/22 20:03:53 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*n_str;
	int		i;

	if (!s || !f)
		return (NULL);
	n_str = (char *)gc_malloc(ft_strlen(s) + 1);
	if (n_str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		n_str[i] = f(i, s[i]);
		i++;
	}
	n_str[i] = '\0';
	return (n_str);
}
