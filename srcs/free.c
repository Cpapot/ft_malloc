/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:49:38 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/10 15:12:34 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc_intern.h"

void free(void *ptr)
{
	if (ptr == NULL)
		return ;
	t_malloc_block *current = mallocData.allocatedData;

	while (current != NULL)
	{
		if (ptr >= current->blockStart && ptr < current->blockStart + current->totalSize)
		{
			if (current->zoneType != LARGE)
			{
				t_malloc_pool *currentPool = current->pool;
				while (currentPool != NULL)
				{
					if (ptr == currentPool->ptr)
					{
						block_free_debug(current, ptr, currentPool->size);
						clean_freed_memory(ptr, currentPool->size);
						currentPool->isAllocated = false;
						current->emptyPool++;
						if (current->emptyPool == current->totalPool)
						{
							if (free_block(current) == false)
							{
								write(2, "Error: failed to free block\n", 29);
								return ;
							}
						}
						break ;
					}
					currentPool = currentPool->next;
				}
			}
			else
			{
				clean_freed_memory(ptr, current->totalSize);
				block_free_debug(current, ptr, current->totalSize);
				if (free_block(current) == false)
				{
					write(2, "Error: failed to free block\n", 29);
					return ;
				}
			}

			return ;
		}
		current = current->next;
	}
}
