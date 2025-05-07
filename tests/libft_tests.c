/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:03:26 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/07 17:03:29 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "../libft/includes/libft.h"

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}

void test_ft_strdup()
{
	safe_print("=== Test ft_strdup ===\n");
	t_memlist *mem = NULL;
	char *original = "Hello, World!";
	char *duplicate = ft_strdup(original, &mem);

	if (duplicate && strcmp(original, duplicate) == 0)
		safe_print("ft_strdup: OK\n");
	else
		safe_print("ft_strdup: KO\n");

	stock_free(&mem);
}

void test_ft_strjoin()
{
	safe_print("=== Test ft_strjoin ===\n");
	t_memlist *mem = NULL;
	char *s1 = "Hello, ";
	char *s2 = "World!";
	char *joined = ft_strjoin(s1, s2, &mem);

	if (joined && strcmp(joined, "Hello, World!") == 0)
		safe_print("ft_strjoin: OK\n");
	else
		safe_print("ft_strjoin: KO\n");

	stock_free(&mem);
}

void test_ft_strtrim()
{
	safe_print("=== Test ft_strtrim ===\n");
	char *str = "  Hello, World!  ";
	char *trimmed = ft_strtrim(str, " ");

	if (trimmed && strcmp(trimmed, "Hello, World!") == 0)
		safe_print("ft_strtrim: OK\n");
	else
		safe_print("ft_strtrim: KO\n");

	free(trimmed);
}

void test_ft_split()
{
	safe_print("=== Test ft_split ===\n");
	t_memlist *mem = NULL;
	char *str = "Hello,World,Split,Test";
	char **parts = ft_split(str, ",", &mem);

	if (parts)
	{
		if (parts[0] && strcmp(parts[0], "Hello") == 0 &&
			parts[1] && strcmp(parts[1], "World") == 0 &&
			parts[2] && strcmp(parts[2], "Split") == 0 &&
			parts[3] && strcmp(parts[3], "Test") == 0 &&
			parts[4] == NULL)
			safe_print("ft_split: OK\n");
		else
			safe_print("ft_split: KO\n");

		stock_free(&mem); // Clear all memory at once
	}
	else
	{
		safe_print("ft_split: KO (NULL return)\n");
	}
}

void test_ft_itoa()
{
	safe_print("=== Test ft_itoa ===\n");
	int n1 = 42;
	int n2 = -42;
	int n3 = 0;

	char *s1 = ft_itoa(n1);
	char *s2 = ft_itoa(n2);
	char *s3 = ft_itoa(n3);

	if (s1 && strcmp(s1, "42") == 0 &&
		s2 && strcmp(s2, "-42") == 0 &&
		s3 && strcmp(s3, "0") == 0)
		safe_print("ft_itoa: OK\n");
	else
		safe_print("ft_itoa: KO\n");

	free(s1);
	free(s2);
	free(s3);
}

void test_ft_calloc()
{
	safe_print("=== Test ft_calloc ===\n");
	size_t size = 5;
	int *array = (int *)ft_calloc(size, sizeof(int));

	if (array)
	{
		int is_zeroed = 1;
		for (size_t i = 0; i < size; i++)
		{
			if (array[i] != 0)
			{
				is_zeroed = 0;
				break;
			}
		}

		if (is_zeroed)
			safe_print("ft_calloc: OK\n");
		else
			safe_print("ft_calloc: KO (memory not zeroed)\n");

		free(array); // Free the allocated memory
	}
	else
	{
		safe_print("ft_calloc: KO (NULL return)\n");
	}
}

void test_ft_lstnew()
{
	safe_print("=== Test ft_lstnew ===\n");
	t_memlist *mem = NULL;
	int content = 42;
	t_list *node = ft_lstnew(&content, &mem);

	if (node && *(int *)(node->content) == 42 && node->next == NULL)
		safe_print("ft_lstnew: OK\n");
	else
		safe_print("ft_lstnew: KO\n");

	stock_free(&mem); // Clear all memory at once
}

void *map_function(void *content)
{
	int *num = (int *)content;
	int *new_num = malloc(sizeof(int));
	if (new_num)
		*new_num = *num * 2;
	return new_num;
}

void test_stock_malloc()
{
	safe_print("=== Test stock_malloc/stock_free ===\n");
	t_memlist *mem = NULL;
	void *ptr = stock_malloc(10, &mem);

	if (ptr)
	{
		safe_print("stock_malloc: OK\n");
		// Try to free it
		stock_free(&mem);
		safe_print("stock_free: seems OK (no crash)\n");
	}
	else
	{
		safe_print("stock_malloc: KO (NULL return)\n");
	}
}

int main(void)
{
	safe_print("Starting libft malloc function tests...\n\n");

	test_ft_strdup();
	test_ft_strjoin();
	test_ft_strtrim();
	test_ft_split();
	test_ft_itoa();
	test_ft_calloc();
	test_ft_lstnew();
	test_stock_malloc();

	safe_print("\nAll tests completed.\n");
	return 0;
}
