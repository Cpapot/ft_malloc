/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:18:35 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/10 15:12:53 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc_intern.h"
#include "../inc/str_utils.h"


void	show_alloc_mem_ex()
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
					puthexadump(currentPool->ptr, currentPool->size);
					putstr("\n");
					totalBytes += currentPool->size;
				}
				currentPool = currentPool->next;
			}
		}
		else
		{
			putptr(current->blockStart), putstr(" - "), putptr(current->blockStart + current->totalSize);
			putstr(" : "), putnbr(current->totalSize), putstr(" bytes\n");
			puthexadump(current->blockStart, current->totalSize);
			putstr("\n");
			totalBytes += current->totalSize;
		}
		current = current->next;
	}
	putstr("Total : "), putnbr(totalBytes), putstr(" bytes\n"), putstr("Total allocated : "), putnbr(totalAllocatedBytes), putstr(" bytes\n");
}
