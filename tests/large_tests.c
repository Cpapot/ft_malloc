/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:03:31 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/08 16:41:00 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "../libft/includes/libft.h"
#include "../inc/malloc.h"

# define LARGE_SIZE			1000000
# define VERY_LARGE_SIZE	1000000000
# define TINY_SIZE			16

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}

void test_large_malloc()
{
	safe_print("=== Test large malloc ===\n");

	void *ptr = malloc(LARGE_SIZE);

	if (ptr)
	{
		safe_print("malloc: OK\n");
		free(ptr);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_multiple_large_malloc()
{
	safe_print("=== Test multiple large malloc ===\n");
	void *ptr1 = malloc(LARGE_SIZE);
	void *ptr2 = malloc(LARGE_SIZE);
	void *ptr3 = malloc(LARGE_SIZE);
	if (ptr1 && ptr2 && ptr3)
	{
		safe_print("malloc: OK\n");
		free(ptr1);
		free(ptr2);
		free(ptr3);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_writing_large_malloc()
{
	safe_print("=== Test writing large malloc ===\n");
	void *ptr1 = malloc(LARGE_SIZE);

	if (ptr1)
	{
		safe_print("malloc: OK\n");
		memset(ptr1, 'A', LARGE_SIZE);
		if (memcmp(ptr1, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 64) == 0)
			safe_print("writing: OK\n");
		else
			safe_print("writing: KO\n");
		free(ptr1);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}


void test_large_realloc()
{
	safe_print("=== Test large realloc ===\n");
	void *ptr = malloc(LARGE_SIZE);
	if (ptr)
	{
		safe_print("malloc: OK\n");
		memset(ptr, 'A', LARGE_SIZE);
		void *new_ptr = realloc(ptr, LARGE_SIZE * 2);
		if (new_ptr && memcmp(new_ptr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 64) == 0)
		{
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO (NULL return)\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_small_to_large_realloc()
{
	safe_print("=== Test small to large realloc ===\n");
	void *ptr = malloc(TINY_SIZE);
	if (ptr)
	{
		safe_print("malloc: OK\n");
		memset(ptr, 'A', TINY_SIZE);
		void *new_ptr = realloc(ptr, LARGE_SIZE );
		if (new_ptr && memcmp(new_ptr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", TINY_SIZE) == 0)
		{
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO (NULL return)\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_very_large_malloc()
{
	safe_print("=== Test very large malloc ===\n");
	void *ptr = malloc(VERY_LARGE_SIZE);
	if (ptr)
	{
		safe_print("malloc: OK\n");
		free(ptr);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_small_and_large_malloc()
{
	t_memlist	*mem = NULL;
	safe_print("=== Test small and large malloc ===\n");
	void *ptr1 = stock_malloc(LARGE_SIZE, &mem);
	void *ptr2 = stock_malloc(LARGE_SIZE, &mem);
	void *ptr3 = stock_malloc(LARGE_SIZE, &mem);
	if (ptr1 && ptr2 && ptr3)
	{
		safe_print("malloc: OK\n");
		stock_free(&mem);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

int main()
{
	safe_print("Starting malloc large tests...\n\n");

	test_large_malloc();
	test_multiple_large_malloc();
	test_small_and_large_malloc();
	test_writing_large_malloc();
	test_large_realloc();
	test_small_to_large_realloc();
	test_very_large_malloc();

	safe_print("\nAll tests completed.\n");
}
