/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:48:01 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/07 15:37:50 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>

# define n		64
# define N		8192
# define m		128
# define M		16384

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
	t_malloc_block		*allocatedData;
	bool				isLeaksDetectorInitialized;
	bool				onClose;
 }	t_malloc_data;

 extern t_malloc_data	mallocData;


 t_malloc_block		*find_free_block(int type);
 void				*allocate_block(size_t size, int type);
 bool				free_block(t_malloc_block *block);
 void				*get_allocated_ptr(t_malloc_block *block, size_t size, int type);

 int				find_zone_type(size_t size);
 size_t				get_zone_size(int type, size_t size);

 void				clean_freed_memory(void *ptr, size_t size);
 void				block_allocate_debug(t_malloc_block *block);
 void				block_free_debug(t_malloc_block *block, void *ptr, size_t size);
 void				exit_debug();

 void				ft_free(void *ptr);
 void				*ft_malloc(size_t size);
 void				*ft_realloc(void *ptr, size_t size);
 void				show_alloc_mem();
 void				show_alloc_mem_ex();


#endif
