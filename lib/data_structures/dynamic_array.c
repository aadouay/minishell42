/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:55:45 by zbakour           #+#    #+#             */
/*   Updated: 2025/06/03 16:43:49 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"

void	array_init(t_array *arr, int capacity, size_t data_size)
{
	arr->array = gc_malloc(capacity * data_size);
	arr->size = 0;
	arr->capacity = capacity;
	arr->data_size = data_size;
	arr->is_empty = true;
}

static void	resize_array(t_array *arr)
{
	size_t	i;
	void	*new_data;

	i = 0;
	arr->capacity *= 2;
	new_data = gc_malloc(arr->capacity * arr->data_size);
	if (!new_data)
		return ;
	while (i < arr->size)
	{
		ft_memcpy((char *)new_data + (i * arr->data_size), (char *)arr->array
			+ (i * arr->data_size), arr->data_size);
		i++;
	}
	arr->array = new_data;
}

void	add_element(t_array *arr, void *value)
{
	if (arr->size == (size_t)arr->capacity)
		resize_array(arr);
	ft_memcpy((char *)arr->array + (arr->size * arr->data_size), value,
		arr->data_size);
	arr->size++;
	arr->is_empty = false;
}

void	*get_element(t_array *arr, int index)
{
	return ((char *)arr->array + (index * arr->data_size));
}

void	free_array(t_array *arr)
{
	free(arr->array);
	arr->size = 0;
	arr->capacity = 0;
	arr->is_empty = true;
}
