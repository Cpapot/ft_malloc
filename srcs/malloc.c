/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:49:36 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/07 15:23:09 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include "../inc/str_utils.h"

t_malloc_data mallocData = {NULL, false, false};

void init_leaks_detector()
{
	if (mallocData.isLeaksDetectorInitialized)
		return ;
	mallocData.isLeaksDetectorInitialized = true;
	if (atexit(exit_debug) != 0)
		putstr("Error registering debug function\n");
}

void	*ft_malloc(size_t size)
{
	t_malloc_block	*freeBlock	= NULL;
	int				type		= find_zone_type(size);

	init_leaks_detector();
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
