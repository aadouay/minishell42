/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:23 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/30 06:59:55 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	check_limit(int sing, unsigned long number)
{
	if (sing == 1)
	{
		if (number > LONG_MAX)
			return (1);
	}
	else if (sing == -1)
	{
		if (number > (unsigned long)LONG_MAX + 1)
			return (1);
	}
	return (0);
}

int	check_overflow(const char *nptr)
{
	unsigned long	r;
	int				signe;
	int				counter;

	counter = 0;
	r = 0;
	signe = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signe *= -1;
		nptr++;
	}
	while (*nptr != '\0' && (*nptr >= '0' && *nptr <= '9'))
	{
		r = r * 10 + (*nptr - 48);
		nptr++;
		counter++;
	}
	if (counter > 20)
		return (1);
	return (check_limit(signe, r));
}
