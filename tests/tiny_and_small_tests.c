/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_and_small_tests.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:42:50 by cpapot            #+#    #+#             */
/*   Updated: 2025/10/17 16:42:37 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "../libft/includes/libft.h"
#include "../inc/malloc.h"

# define TINY_SIZE			16
# define SMALL_SIZE			128
# define LARGE_SIZE			1000000

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}

void test_tiny_malloc()
{
	safe_print("=== Test tiny malloc ===\n");

	void *ptr = malloc(TINY_SIZE);

	if (ptr) {
		safe_print("malloc: OK\n");
		free(ptr);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_small_malloc()
{
	safe_print("=== Test small malloc ===\n");

	void *ptr = malloc(SMALL_SIZE);

	if (ptr) {
		safe_print("malloc: OK\n");
		free(ptr);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_multiple_tiny_malloc()
{
	safe_print("=== Test multiple tiny malloc ===\n");
	void *ptr1 = malloc(TINY_SIZE);
	void *ptr2 = malloc(TINY_SIZE);
	void *ptr3 = malloc(TINY_SIZE);
	if (ptr1 && ptr2 && ptr3) {
		show_alloc_mem_ex();
		safe_print("malloc: OK\n");
		free(ptr1);
		free(ptr2);
		free(ptr3);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_multiple_small_malloc()
{
	safe_print("=== Test multiple small malloc ===\n");
	void *ptr1 = malloc(SMALL_SIZE);
	void *ptr2 = malloc(SMALL_SIZE);
	void *ptr3 = malloc(SMALL_SIZE);
	if (ptr1 && ptr2 && ptr3) {
		safe_print("malloc: OK\n");
		free(ptr1);
		free(ptr2);
		free(ptr3);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_writing_tiny_malloc()
{
	safe_print("=== Test writing tiny malloc ===\n");
	void *ptr1 = malloc(TINY_SIZE);

	if (ptr1) {
		safe_print("malloc: OK\n");
		memset(ptr1, 'A', TINY_SIZE);
		if (memcmp(ptr1, "AAAAAAAAAAAAAAAA", TINY_SIZE) == 0)
			safe_print("writing: OK\n");
		else
			safe_print("writing: KO\n");
		free(ptr1);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_writing_small_malloc()
{
	safe_print("=== Test writing small malloc ===\n");
	void *ptr1 = malloc(SMALL_SIZE);

	if (ptr1) {
		safe_print("malloc: OK\n");
		memset(ptr1, 'B', SMALL_SIZE);
		if (memcmp(ptr1, "BBBBBBBBBBBBBBBB", 16) == 0)
			safe_print("writing: OK\n");
		else
			safe_print("writing: KO\n");
		free(ptr1);
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_tiny_realloc()
{
	safe_print("=== Test tiny realloc ===\n");
	void *ptr = malloc(TINY_SIZE);
	if (ptr) {
		safe_print("malloc: OK\n");
		memset(ptr, 'A', TINY_SIZE);
		void *new_ptr = realloc(ptr, TINY_SIZE * 2);
		if (new_ptr && memcmp(new_ptr, "AAAAAAAAAAAAAAAA", TINY_SIZE) == 0) {
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_small_realloc()
{
	safe_print("=== Test small realloc ===\n");
	void *ptr = malloc(SMALL_SIZE);
	if (ptr) {
		safe_print("malloc: OK\n");
		memset(ptr, 'B', SMALL_SIZE);
		void *new_ptr = realloc(ptr, SMALL_SIZE * 2);
		if (new_ptr && memcmp(new_ptr, "BBBBBBBBBBBBBBBB", 16) == 0) {
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_tiny_to_small_realloc()
{
	safe_print("=== Test tiny to small realloc ===\n");
	void *ptr = malloc(TINY_SIZE);
	if (ptr) {
		safe_print("malloc: OK\n");
		memset(ptr, 'A', TINY_SIZE);
		void *new_ptr = realloc(ptr, SMALL_SIZE);
		if (new_ptr && memcmp(new_ptr, "AAAAAAAAAAAAAAAA", TINY_SIZE) == 0) {
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_small_to_large_realloc()
{
	safe_print("=== Test small to large realloc ===\n");
	void *ptr = malloc(SMALL_SIZE);
	if (ptr) {
		safe_print("malloc: OK\n");
		memset(ptr, 'B', SMALL_SIZE);
		void *new_ptr = realloc(ptr, LARGE_SIZE);
		if (new_ptr && memcmp(new_ptr, "BBBBBBBBBBBBBBBB", 16) == 0) {
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_realloc_smaller()
{
	safe_print("=== Test realloc to smaller size ===\n");
	void *ptr = malloc(SMALL_SIZE);
	if (ptr) {
		safe_print("malloc: OK\n");
		memset(ptr, 'B', SMALL_SIZE);
		void *new_ptr = realloc(ptr, TINY_SIZE);
		if (new_ptr && memcmp(new_ptr, "BBBBBBBBBBBBBBBB", TINY_SIZE) == 0) {
			safe_print("realloc: OK\n");
			free(new_ptr);
		}
		else
			safe_print("realloc: KO\n");
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_realloc_null_ptr()
{
	safe_print("=== Test realloc with NULL pointer ===\n");
	void *ptr = realloc(NULL, SMALL_SIZE);
	if (ptr) {
		safe_print("realloc NULL: OK (acts like malloc)\n");
		free(ptr);
	}
	else
		safe_print("realloc NULL: KO\n");
}

void test_realloc_zero_size()
{
	safe_print("=== Test realloc with zero size ===\n");
	void *ptr = malloc(TINY_SIZE);
	if (ptr) {
		safe_print("malloc: OK\n");
		void *new_ptr = realloc(ptr, 0);
		if (new_ptr == NULL)
			safe_print("realloc zero: OK (acts like free)\n");
		else {
			safe_print("realloc zero: KO (expected NULL)\n");
			free(new_ptr);
		}
	}
	else
		safe_print("malloc: KO (NULL return)\n");
}

void test_mixed_allocs()
{
	safe_print("=== Test mixed tiny and small allocations ===\n");
	void *ptrs[10];
	int i;

	for (i = 0; i < 10; i++) {
		ptrs[i] = malloc(i % 2 ? TINY_SIZE : SMALL_SIZE);
		if (!ptrs[i]) {
			safe_print("mixed allocs: KO\n");
			for (int j = 0; j < i; j++)
				free(ptrs[j]);
			return;
		}
	}

	for (i = 9; i >= 0; i--)
		free(ptrs[i]);

	safe_print("mixed allocs: OK\n");
}

int main()
{
	safe_print("Starting malloc tiny and small tests...\n\n");

	test_tiny_malloc();
	test_small_malloc();
	test_multiple_tiny_malloc();
	test_multiple_small_malloc();
	test_writing_tiny_malloc();
	test_writing_small_malloc();
	test_tiny_realloc();
	test_small_realloc();
	test_tiny_to_small_realloc();
	test_small_to_large_realloc();
	test_realloc_smaller();
	test_realloc_null_ptr();
	test_realloc_zero_size();
	test_mixed_allocs();

	safe_print("\nAll tests completed.\n");
}
