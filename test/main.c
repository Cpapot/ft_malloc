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
	void *ptr = malloc(42);
	safe_print("Allocated pointer: %p\n");

	// Test realloc
	void *new_ptr = realloc(ptr, 100);
	safe_print("Reallocated pointer: %p\n");

	// Test free
	free(new_ptr);

	safe_print("Memory tests completed\n");
	return (0);
}

//gcc -g -o test_main ./test/main.c -L. -lft_malloc -Wl,-rpath=$(pwd)
