/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:49:34 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/06 22:13:42 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*memcpy(void *dst, const void *src, size_t size)
{
	int	i;

	i = 0;
	if ((int)size == 0)
		return (dst);
	while (i != (int)size)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void	*delete_and_copy(void *ptr, size_t oldSize, size_t size)
{
	void *newPtr = ft_malloc(size);
	if (newPtr == NULL)
		return (NULL);
	newPtr = memcpy(newPtr, ptr, oldSize);
	ft_free(ptr);
	return (newPtr);
}

void *ft_realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	t_malloc_block *current = mallocData.allocatedData;
	while (current != NULL)
	{
		if (ptr >= current->blockStart && ptr < current->blockStart + current->totalSize)
		{
			if ((current->zoneType == TINY && size <= n) || (current->zoneType == SMALL && size <= m))
			{
				t_malloc_pool *currentPool = current->pool;
				while (currentPool != NULL)
				{
					if (ptr == currentPool->ptr)
					{
						currentPool->size = size;
					}
					currentPool = currentPool->next;
				}
				return (ptr);
			}
			else
				return delete_and_copy(ptr, current->zoneType == LARGE ? current->totalSize : current->poolSize, size);
		}
	}
	return (NULL);
}
