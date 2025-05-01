/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:48:01 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/01 11:37:07 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# define n		32
# define N		4096
# define m		256
# define M		32768

typedef struct malloc_block
{
	void					*ptr;
	size_t					size;
	bool					isAllocated;
	struct malloc_block		*next;
	struct malloc_block		*prev;
}	t_malloc_block;

extern t_malloc_block	*allocatedData;

// les premiers sont pour la liste chainee

 void				*find_free_block(size_t size);
 bool				malloc_add_lst(size_t size);

 void				ft_free(void *ptr);
 void				*ft_malloc(size_t size);
 void				*ft_realloc(void *ptr, size_t size);

#endif
