#include <unistd.h>
#include <string.h>
#include "../libft/includes/libft.h"
#include "../inc/malloc.h"

#define SIZE 5000

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}

int		main()
{
	char *buffer[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		buffer[i] = malloc(SIZE);
		if (buffer[i] == NULL)
		{
			safe_print("malloc: KO (NULL return)\n");
			return 1;
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		free(buffer[i]);
	}
	return 0;
}
