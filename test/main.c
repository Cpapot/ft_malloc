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


	for(int i = 0; i < 500; i++)
	{
		ft_malloc(sizeof(char) * 128);
	}
	for(int i = 0; i < 500; i++)
	{
		ft_malloc(sizeof(char) * 64);
	}
	// ft_free(ptr);
	// ft_free(scdptr);
	// Test realloc
	// void *new_ptr = ft_realloc(ptr, 100);
	// safe_print("Reallocated pointer: %p\n");

	// // Test free
	// ft_free(new_ptr);
	safe_print("\n");
	show_alloc_mem();

	safe_print("Memory tests completed\n");
	return (0);
}

//gcc -g -o test_main ./test/main.c -L. -lft_malloc -Wl,-rpath=$(pwd)
