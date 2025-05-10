/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:15:44 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/10 15:12:45 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc_intern.h"

int	find_zone_type(size_t size)
{
	if (size == 0)
		return EMPTY;
	else if (size <= n)
		return TINY;
	else if (size <= m)
		return SMALL;
	else
		return LARGE;
}

size_t		find_pagesize_multiple(size_t size)
{
	size_t	page_size = sysconf(_SC_PAGESIZE);

	if (size % page_size == 0)
		return size;
	else
		return ((size / page_size) + 1) * page_size;
}

size_t	get_zone_size(int type, size_t size)
{
	if (type == TINY)
		return N + (N / n) * sizeof(t_malloc_pool);
	else if (type == SMALL)
		return M + (M / m) * sizeof(t_malloc_pool);
	else
		return size;
}

void	*get_allocated_ptr(t_malloc_block *block, size_t size, int type)
{
	if (type == LARGE)
		return (block->blockStart);
	t_malloc_pool *current = block->pool;
	while (current != NULL)
	{
		if (current->isAllocated == false)
		{
			block->emptyPool--;
			current->isAllocated = true;
			current->size = size;
			return (current->ptr);
		}
		current = current->next;
	}
	return (NULL);
}
