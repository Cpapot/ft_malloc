/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_block_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:12 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/05 18:29:16 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include <bits/mman-linux.h>

t_malloc_block *allocatedData = NULL;

void		*find_free_block(int type)
{
	t_malloc_block	*current = allocatedData;

	while (current != NULL)
	{
		if (current->zoneType == type && current->emptyPool > 0)
		{
			//current->isAllocated = true;
			printf("found free pool for type %d in block %p\n", type, current->blockStart);
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

void pool_add(t_malloc_pool **pool, t_malloc_pool *new)
{
	if (*pool == NULL)
	{
		printf("pool is NULL\n");
		*pool = new;
		new->next = NULL;
	}
	else
	{
		t_malloc_pool *current = *pool;
		while (current->next != NULL)
			current = current->next;
		//printf("pool is not NULL\n");
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

// quand on appelle cette fonction on doit deja avoir verifier qu'il n'y a pas de block libre dans la liste
// TODO: peut etre ajouter le block au debut de la liste si elle n'est pas vide pour eviter de la parcourir a chaque fois si il reste de la place dans le block (TINY & SMALL allocation)
void		*malloc_add_lst(size_t size, int type)
{
	// quand on alloue un block de memoire on ajoute la taille de la liste tel que mmap(size + sizeof(t_malloc_block *)) puis on l'ajoute a la suite de la liste
	// et si la liste est vide on l'ajoute au debut
	size_t	zone_size = get_zone_size(type, size);

	void	*data = mmap(NULL, zone_size + sizeof(t_malloc_block *),
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (data == MAP_FAILED)
		return (NULL);

	printf("mmap success for block(type: %d) of %zu bytes at: %p\n", type, zone_size + sizeof(t_malloc_block *) , data);

	t_malloc_block *new_block = (t_malloc_block *)data;
	// penser a free t_malloc_block
	new_block->blockStart = (void *)((char *)data + sizeof(t_malloc_block));
	new_block->totalSize = zone_size;
	new_block->next = NULL;
	new_block->zoneType = type;
	if (allocatedData == NULL)
	{
		new_block->prev = NULL;
		allocatedData = new_block;
	}
	else
	{
		t_malloc_block *last = allocatedData;
		while (last->next != NULL)
			last = last->next;
		last->next = new_block;
		new_block->prev = last;
	}
	populate_pool(new_block, type);
	return (new_block);

}

void		*allocate_block(t_malloc_block *block, size_t size, int type)
{
	//on trouve le block de la pool qui est libre on return le ptr et on set isAllocated a true
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
