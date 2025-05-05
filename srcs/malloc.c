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

//LARGE NOT IMPLEMENTED YET
void	*ft_malloc(size_t size)
{
	t_malloc_block	*freeBlock = NULL;
	int type = find_zone_type(size);
	if (type == 0)
		return (NULL);

	printf("\ntype: %d\n", type);

	freeBlock = find_free_block(type);
	if (freeBlock == NULL)
	{
		printf("no empty block found, allocating...\n");
		freeBlock = malloc_add_lst(size, type);
		if (freeBlock == NULL)
		{
			printf("mmap failed\n");
			return (NULL);
		}
		return allocate_block(freeBlock, size, type);
	}
	else
	{
		return allocate_block(freeBlock, size, type);
	}

	// on check si dans la liste chainee il y a un block de memoire libre
	// si oui on le renvoie a la bonne taille
	// sinon on mmap un nouveau block de memoire
	// on l'ajoute a la liste chainee
	// on renvoie le block de memoire
	return (NULL);
}
