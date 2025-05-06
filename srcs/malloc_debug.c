/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:18:51 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/06 23:20:59 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include "../inc/str_utils.h"

/*
	MALLOC_SHOW_LEAKS
	MALLOC_FREE_LEAKS
	MALLOC_SHOW_ALLOCATE
	MALLOC_SHOW_FREE
	MALLOC_SHOW_HEXADUMP, tout ce qui viens des variables d'environnement est montrer en hexa
	MALLOC_CLEAN_FREED_MEMORY, memset a 0 les memory freed

*/

static bool is_env_var_set(const char *var)
{
	char *env_var = getenv(var);
	return (env_var != NULL && env_var[0] != '0' && env_var[0] != '\0');
}

void block_allocate_debug()
{
	if (is_env_var_set("MALLOC_DUMP_ALLOCATE"))
	{

	}
}

void block_free_debug()
{
	if (is_env_var_set("MALLOC_DUMP_FREE"))
	{

	}
}

void exit_debug() {
	if (is_env_var_set("MALLOC_SHOW_LEAKS"))
	{
		putstr("\n");
		if (mallocData.allocatedData != NULL)
			putstr("\e[0;31m");
		else
			putstr("\e[0;32m");
		putstr("(MALLOC_DUMP_LEAKS) STILL ALLOCATED DATA:\n");
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
