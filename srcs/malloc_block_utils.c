/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_block_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:12 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/10 15:12:39 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc_intern.h"
#include <bits/mman-linux.h>

t_malloc_block		*find_free_block(int type)
{
	t_malloc_block	*current = mallocData.allocatedData;

	while (current != NULL)
	{
		if (current->zoneType == type && current->emptyPool > 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void pool_add(t_malloc_pool **pool, t_malloc_pool *new)
{
	if (*pool == NULL)
	{
		*pool = new;
		new->next = NULL;
	}
	else
	{
		t_malloc_pool *current = *pool;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
		new->next = NULL;
	}
}

void	populate_pool(t_malloc_block *block, int type)
{
	if (type == TINY)
	{
		block->emptyPool = N / n;
		block->poolSize = n;
		block->totalPool = N / n;
		block->pool = NULL;
		for (size_t i = 0; i < block->emptyPool; i++)
		{
			t_malloc_pool *newPool = (t_malloc_pool*)((char*)block->blockStart + (sizeof(t_malloc_pool) + n) * i);
			newPool->isAllocated = false;
			newPool->ptr = (char *)block->blockStart + (sizeof(t_malloc_pool) + n) * i + sizeof(t_malloc_pool);
			newPool->size = n;
			pool_add(&block->pool, newPool);
		}
	}
	else if (type == SMALL)
	{
		block->emptyPool = M / m;
		block->totalPool = M / m;
		block->poolSize = m;
		block->pool = NULL;
		for (size_t i = 0; i < block->emptyPool; i++)
		{
			t_malloc_pool *newPool = (t_malloc_pool*)((char*)block->blockStart + (sizeof(t_malloc_pool) + m) * i);
			newPool->isAllocated = false;
			newPool->ptr = (char *)block->blockStart + (sizeof(t_malloc_pool) + m) * i + sizeof(t_malloc_pool);
			newPool->size = m;
			pool_add(&block->pool, newPool);
		}
	}
	else
	{
		block->pool = NULL;
		block->emptyPool = 0;
		block->totalPool = 0;
		block->poolSize = 0;
	}
}

bool	free_block(t_malloc_block *block)
{
	if (block->prev != NULL)
		block->prev->next = block->next;
	if (block->next != NULL)
		block->next->prev = block->prev;
	if (mallocData.allocatedData == block)
		mallocData.allocatedData = block->next;
	if (munmap(block, find_pagesize_multiple(block->totalSize + sizeof(t_malloc_block *))) == -1)
		return false;
	return true;
}

void		*allocate_block(size_t size, int type)
{
	size_t	zone_size = get_zone_size(type, size);

	void	*data = mmap(NULL, find_pagesize_multiple(zone_size + sizeof(t_malloc_block *)),
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (data == MAP_FAILED)
		return (NULL);

	t_malloc_block *new_block = (t_malloc_block *)data;
	new_block->blockStart = (void *)((char *)data + sizeof(t_malloc_block));
	new_block->totalSize = zone_size;
	new_block->next = NULL;
	new_block->zoneType = type;
	if (mallocData.allocatedData == NULL)
	{
		new_block->prev = NULL;
		mallocData.allocatedData = new_block;
	}
	else
	{
		t_malloc_block *last = mallocData.allocatedData;
		while (last->next != NULL)
			last = last->next;
		last->next = new_block;
		new_block->prev = last;
	}
	populate_pool(new_block, type);
	block_allocate_debug(new_block);
	return (new_block);

}
