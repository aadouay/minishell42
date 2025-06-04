/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:22:46 by ayadouay          #+#    #+#             */
/*   Updated: 2025/05/31 15:22:48 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *str, char *error)
{
	error = ft_strjoin(str, error);
	write(2, ft_strjoin(error, "\n"), ft_strlen(error) + 1);
}
