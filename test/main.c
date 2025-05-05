#include <unistd.h>
#include <string.h>
#include "../inc/malloc.h"

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}



int main(void)
{
	safe_print("\nStarting memory allocation tests\n");

	// Test malloc
	// void *ptr = ft_malloc(sizeof(char) * 100);
	// void *scdptr = ft_malloc(sizeof(char) * 100);


	void *smallptr = ft_malloc(sizeof(char) * 128);
	
	void *tinyptr = ft_malloc(sizeof(char) * 64);

	void *largeptr = ft_malloc(sizeof(char) * 20000);

	safe_print("\n");
	show_alloc_mem();

	ft_free(smallptr);

	ft_free(largeptr);

	safe_print("\n");

	show_alloc_mem();

	safe_print("\n");

	tinyptr = ft_realloc(tinyptr, 50);

	for (int i = 0; i < 50; i++)
	{
		((char *)tinyptr)[i] = 'a';
	}
	((char *)tinyptr)[49] = '\0';

	safe_print(tinyptr);
	safe_print("\n");

	show_alloc_mem();

	tinyptr = ft_realloc(tinyptr, 10000);

	safe_print(tinyptr);
	safe_print("\n");

	safe_print("\n");

	show_alloc_mem();

	ft_free (tinyptr);

	safe_print("\n");

	show_alloc_mem();

	safe_print("\n");

	safe_print("Memory tests completed\n");
	return (0);
}

//gcc -g -o test_main ./test/main.c -L. -lft_malloc -Wl,-rpath=$(pwd)
