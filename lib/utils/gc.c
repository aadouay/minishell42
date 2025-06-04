/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:32:42 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/31 16:07:20 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_malloc(size_t size)
{
	void		*ptr;
	t_gc_node	*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = g_minishell.gc.head;
	g_minishell.gc.head = node;
	return (ptr);
}

void	gc_clear(void)
{
	t_gc_node	*current;
	t_gc_node	*tmp;

	current = g_minishell.gc.head;
	while (current)
	{
		if (current->ptr)
			free(current->ptr);
		tmp = current;
		current = current->next;
		if (tmp)
			free(tmp);
	}
	g_minishell.gc.head = NULL;
}
