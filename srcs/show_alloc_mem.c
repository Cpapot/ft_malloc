/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:11:05 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/08 17:16:36 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include "../inc/str_utils.h"


void	show_alloc_mem()
{
	size_t		totalBytes = 0;
	size_t		totalAllocatedBytes = 0;

	t_malloc_block *current = mallocData.allocatedData;
	while (current != NULL)
	{
		totalAllocatedBytes += find_pagesize_multiple(current->totalSize + sizeof(t_malloc_block *));
		putTypeAndPtr(current->zoneType, current->blockStart);
		if (current->zoneType == 1 || current->zoneType == 2)
		{
			putstr(", "), putnbr(current->emptyPool), putstr("/"), putnbr(current->totalPool);
			putstr(" empty pool of "), putnbr(current->poolSize), putstr(" bytes\n");

			t_malloc_pool *currentPool = current->pool;
			while (currentPool != NULL)
			{
				if (currentPool->isAllocated == true)
				{
					putptr(currentPool->ptr), putstr(" - "), putptr((void *)(currentPool->ptr + currentPool->size));
					putstr(" : "), putnbr(currentPool->size), putstr(" bytes\n");
					totalBytes += currentPool->size;
				}
				currentPool = currentPool->next;
			}
		}
		else
		{
			putptr(current->blockStart), putstr(" - "), putptr(current->blockStart + current->totalSize);
			putstr(" : "), putnbr(current->totalSize), putstr(" bytes\n");
			totalBytes += current->totalSize;
		}
		current = current->next;
	}
	putstr("Total : "), putnbr(totalBytes), putstr(" bytes\n"), putstr("Total allocated : "), putnbr(totalAllocatedBytes), putstr(" bytes\n");
}
