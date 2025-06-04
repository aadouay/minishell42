/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:49:14 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 14:49:15 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_array(char **arr)
{
	int		swapped;
	int		i;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (arr[i + 1])
		{
			if (strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}
