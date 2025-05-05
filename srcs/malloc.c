/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:49:36 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/05 18:07:37 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*ft_malloc(size_t size)
{
	t_malloc_block	*freeBlock = NULL;
	int type = find_zone_type(size);
	if (type == 0)
		return (NULL);

	freeBlock = find_free_block(type);
	if (freeBlock == NULL)
	{
		freeBlock = allocate_block(size, type);
		if (freeBlock == NULL)
			return (NULL);
		return get_allocated_ptr(freeBlock, size, type);
	}
	else
		return get_allocated_ptr(freeBlock, size, type);
}
