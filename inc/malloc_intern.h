/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_intern.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:07:04 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/10 15:14:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_INTERN_H
# define MALLOC_INTERN_H

# include "malloc.h"

enum e_zone
{
	EMPTY = 0,
	TINY,
	SMALL,
	LARGE
};

typedef struct malloc_pool
{
	bool					isAllocated;
	void					*ptr;
	size_t					size;
	struct malloc_pool		*next;
}	t_malloc_pool;

typedef struct malloc_block
{
	void					*blockStart;
	size_t					totalSize;
	unsigned char			zoneType;
	unsigned int			poolSize; // 0 si block est LARGE
	unsigned int			totalPool; // 0 si block est LARGE
	unsigned int			emptyPool; // 0 si block est LARGE
	t_malloc_pool			*pool;	// NULL si block est LARGE
	struct malloc_block		*next;
	struct malloc_block		*prev;
}	t_malloc_block;

typedef struct malloc_data
{
	t_malloc_block			*allocatedData;
	bool					isLeaksDetectorInitialized;
	bool					onClose;
}	t_malloc_data;

extern t_malloc_data		mallocData;

t_malloc_block				*find_free_block(int type);
void						*allocate_block(size_t size, int type);
bool						free_block(t_malloc_block *block);
void						*get_allocated_ptr(t_malloc_block *block, size_t size, int type);

int							find_zone_type(size_t size);
size_t						find_pagesize_multiple(size_t size);
size_t						get_zone_size(int type, size_t size);

void						clean_freed_memory(void *ptr, size_t size);
void						block_allocate_debug(t_malloc_block *block);
void						block_free_debug(t_malloc_block *block, void *ptr, size_t size);
void						exit_debug();

#endif
