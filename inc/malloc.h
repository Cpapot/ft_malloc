/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:48:01 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/05 17:29:56 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# define n		64
# define N		32000
# define m		128
# define M		64000

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
	int						zoneType;
	size_t					poolSize; // 0 si block est LARGE
	size_t					totalPool; // 0 si block est LARGE
	size_t					emptyPool; // 0 si block est LARGE
	t_malloc_pool			*pool;	// NULL si block est LARGE
	struct malloc_block		*next;
	struct malloc_block		*prev;
}	t_malloc_block;


extern t_malloc_block	*allocatedData;

// les premiers sont pour la liste chainee

 void				*find_free_block(int type);
 void				*malloc_add_lst(size_t size, int type);
 void				*allocate_block(t_malloc_block *block, size_t size, int type);

 int				find_zone_type(size_t size);
 size_t				get_zone_size(int type, size_t size);

 void				ft_free(void *ptr);
 void				*ft_malloc(size_t size);
 void				*ft_realloc(void *ptr, size_t size);
 void				show_alloc_mem();


#endif
