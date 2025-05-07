/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:18:51 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/07 16:20:58 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include "../inc/str_utils.h"

/*
	MALLOC_SHOW_LEAKS
	MALLOC_FREE_LEAKS
	MALLOC_SHOW_ALLOCATE
	MALLOC_SHOW_FREE
	MALLOC_SHOW_MUNMAP
	MALLOC_SHOW_HEXADUMP, tout ce qui viens des variables d'environnement est montrer en hexa
	MALLOC_CLEAN_FREED_MEMORY, memset a 0 les memory freed

*/

static bool is_env_var_set(const char *var)
{
	char *env_var = getenv(var);
	return (env_var != NULL && env_var[0] != '0' && env_var[0] != '\0');
}

void clean_freed_memory(void *ptr, size_t size)
{
	if (is_env_var_set("MALLOC_CLEAN_FREED_MEMORY"))
	{
		unsigned char *bytePtr = (unsigned char *)ptr;
		for (size_t i = 0; i < size; i++)
		{
			bytePtr[i] = 0;
		}
	}
}

void block_allocate_debug(t_malloc_block *block)
{
	if (is_env_var_set("MALLOC_SHOW_ALLOCATE"))
	{
		putstr("\e[0;33m(MALLOC_SHOW_ALLOCATE) ALLOCATED BLOCK:\n");
		putTypeAndPtr(block->zoneType == 3 ? 4 : block->zoneType, block->blockStart);
		if (block->zoneType != LARGE)
			putstr(", "), putnbr(block->totalPool), putstr(" pools of "), putnbr(block->poolSize);
		else
			putstr(", of "), putnbr(block->totalSize);
		putstr(" bytes\n\e[0m");
	}
}

void block_free_debug(t_malloc_block *block, void *ptr, size_t size)
{
	if (mallocData.onClose)
		return ;
	if (is_env_var_set("MALLOC_SHOW_FREE"))
	{
		putstr("\e[0;32m(MALLOC_SHOW_FREE) FREE PTR:\n");
		putTypeAndPtr(block->zoneType == 3 ? 4 : block->zoneType, ptr);
		if (is_env_var_set("MALLOC_SHOW_HEXADUMP"))
		{
			putstr(", of "), putnbr(size), putstr(" bytes freed\n");
			puthexadump(ptr, size);
			putstr("\e[0m");
		}
		else
		{
			putstr(", of "), putnbr(size), putstr(" bytes freed\n\e[0m");
		}
	}
	if (is_env_var_set("MALLOC_SHOW_MUNMAP"))
	{
		if (block->zoneType == LARGE || (block->emptyPool + 1 == block->totalPool))
		{
			putstr("\e[0;31m(MALLOC_SHOW_MUNMAP) MUNMAP BLOCK:\n");
			putTypeAndPtr(block->zoneType == 3 ? 4 : block->zoneType, block->blockStart - sizeof(t_malloc_block *));
			putstr(", of "), putnbr(block->totalSize + sizeof(t_malloc_block *));
			putstr(" bytes\n\e[0m");
		}
	}
}

void exit_debug() {
	mallocData.onClose = true;
	if (is_env_var_set("MALLOC_SHOW_LEAKS"))
	{
		putstr("\n");
		if (mallocData.allocatedData != NULL)
			putstr("\e[0;31m");
		else
			putstr("\e[0;32m");
		putstr("(MALLOC_SHOW_LEAKS) STILL ALLOCATED DATA:\n");
		if (is_env_var_set("MALLOC_SHOW_HEXADUMP"))
			show_alloc_mem_ex();
		else
			show_alloc_mem();
		putstr("\e[0m");
	}

	if (is_env_var_set("MALLOC_FREE_LEAKS"))
	{
		putstr("\n");
		if (mallocData.allocatedData != NULL)
		{
			t_malloc_block *current = mallocData.allocatedData;
			while (current != NULL)
			{
				free_block(current);
				current = mallocData.allocatedData;
			}
			putstr("\e[0;31m(MALLOC_FREE_LEAKS) LEAKS CLEANED BEFORE EXIT\n\e[0m");
		}
		else
		{
			putstr("\e[0;32m(MALLOC_FREE_LEAKS) NO LEAKS TO CLEAN\n\e[0m");
		}
	}

}
