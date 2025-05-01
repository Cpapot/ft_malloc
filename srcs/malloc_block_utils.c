/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_block_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:41:12 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/01 11:36:46 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include <bits/mman-linux.h>

t_malloc_block *allocatedData = NULL;

void		*find_free_block(size_t size)
{
	t_malloc_block	*current = allocatedData;

	while (current != NULL)
	{
		if (/*current->isAllocated == false &&*/ current->size >= size)
		{
			//current->isAllocated = true;
			return (current->ptr);
		}
		current = current->next;
	}
	return (NULL);
}

// quand on appelle cette fonction on doit deja avoir verifier qu'il n'y a pas de block libre dans la liste
// TODO: peut etre ajouter le block au debut de la liste si elle n'est pas vide pour eviter de la parcourir a chaque fois si il reste de la place dans le block (TINY & SMALL allocation)
bool		malloc_add_lst(size_t size)
{
	// quand on alloue un block de memoire on ajoute la taille de la liste tel que mmap(size + sizeof(t_malloc_block *)) puis on l'ajoute a la suite de la liste
	// et si la liste est vide on l'ajoute au debut

	void	*data = mmap(NULL, size + sizeof(t_malloc_block *),
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (data == MAP_FAILED)
		return (false);

	t_malloc_block *new_block = (t_malloc_block *)data;
	new_block->ptr = (void *)((char *)data + sizeof(t_malloc_block));
	new_block->size = size;
	new_block->isAllocated = true;
	new_block->next = NULL;
	if (allocatedData == NULL)
	{
		new_block->prev = NULL;
		allocatedData = new_block;
	}
	else
	{
		t_malloc_block *last = allocatedData;
		while (last->next != NULL)
			last = last->next;
		last->next = new_block;
		new_block->prev = last;
	}
	return (true);
}
