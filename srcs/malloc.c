/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:49:36 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/01 11:46:37 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

// void allocate_block(size_t size)
// {
// 	long blockSize = sysconf(_SC_PAGESIZE);
// void *result = mmap(NULL, size, PROT_READ | PROT_WRITE,
// 	MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
// }

void *ft_malloc(size_t size)
{
	if (size == 0)
		return (NULL);

	if (find_free_block(size) == NULL)
	{
		printf("no empty block found, allocating...\n");
		if (malloc_add_lst(size) == false)
		{
			printf("mmap failed\n");
			return (NULL);
		}
		else
		{
			printf("mmap success for block of %ld bytes at: %p\n", sizeof(&allocatedData->ptr) ,(allocatedData)->ptr);
			printf("this block is stored in the allocatedData lst at: %p\n", allocatedData);
			return (allocatedData->ptr);
		}
	}
	else
	{
		printf("found empty block\n");
	}

	// on check si dans la liste chainee il y a un block de memoire libre
	// si oui on le renvoie a la bonne taille
	// sinon on mmap un nouveau block de memoire
	// on l'ajoute a la liste chainee
	// on renvoie le block de memoire

	printf("malloc\n");
	return (NULL);
}
