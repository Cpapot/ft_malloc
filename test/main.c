#include <unistd.h>
#include <string.h>
#include "../inc/malloc.h"

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}

int main(void)
{
	safe_print("Starting memory allocation tests\n");

	// Test malloc
	void *ptr = ft_malloc(420);
	printf("Allocated pointer: %p\n", ptr);

	// Test realloc
	// void *new_ptr = ft_realloc(ptr, 100);
	// safe_print("Reallocated pointer: %p\n");

	// // Test free
	// ft_free(new_ptr);

	safe_print("Memory tests completed\n");
	return (0);
}

//gcc -g -o test_main ./test/main.c -L. -lft_malloc -Wl,-rpath=$(pwd)
