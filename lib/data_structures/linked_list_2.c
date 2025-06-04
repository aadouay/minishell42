/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:44:33 by ayadouay          #+#    #+#             */
/*   Updated: 2025/06/03 16:45:04 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*newcontent;
	t_list	*newnode;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (!newnode)
		{
			del(newcontent);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, newnode);
		lst = lst->next;
	}
	return (head);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)gc_malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*current;

	if (!lst)
		return (0);
	current = lst;
	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}
