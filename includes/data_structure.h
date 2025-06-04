/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:17:05 by zbakour           #+#    #+#             */
/*   Updated: 2025/05/17 14:24:02 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_array
{
	size_t			size;
	bool			is_empty;
	void			*array;
	size_t			data_size;
	int				capacity;
}					t_array;

void				array_init(t_array *arr, int capacity, size_t data_size);
void				add_element(t_array *arr, void *value);
void				*get_element(t_array *arr, int index);
void				free_array(t_array *arr);

char				*make_dynamic_str(void);
char				*dynamic_str_append_char(char *str, char c);
char				*dynamic_str_append_str(char *str, char *s_append);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
#endif