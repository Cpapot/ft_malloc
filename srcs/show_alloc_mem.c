/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:11:05 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/05 18:28:33 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

size_t strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	putstr(char *str)
{
	write(1, str, strlen(str));
}

void	putnbr(unsigned int nbr)
{
	char		str[12];
	int			i;

	i = 0;
	if (nbr == 0)
	{
		putstr("0");
		return ;
	}
	while (nbr > 0)
	{
		str[i] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	while (--i >= 0)
		write(1, &str[i], 1);
}

void putptr(void *ptr)
{
	unsigned long long int	nbr;
	char					str[12];
	int						i;

	nbr = (unsigned long long int)ptr;
	i = 0;
	putstr("0x");
	if (nbr == 0)
	{
		putstr("0");
		return ;
	}
	while (nbr > 0)
	{
		str[i] = (nbr % 16) + '0';
		if (str[i] > '9')
			str[i] += 39;
		nbr /= 16;
		i++;
	}
	while (--i >= 0)
		write(1, &str[i], 1);
}

void putTypeAndPtr(int type, void *ptr)
{
	if (type == 1)
		putstr("TINY : ");
	else if (type == 2)
		putstr("SMALL : ");
	else
		putstr("LARGE : ");
	putptr(ptr);
	if (type == 3)
		putstr("\n");
}

//LARGE NOT IMPLEMENTED YET
void	show_alloc_mem()
{
	size_t		totalBytes = 0;
	size_t		totalAllocatedBytes = 0;

	t_malloc_block *current = allocatedData;
	while (current != NULL)
	{
		totalAllocatedBytes += current->totalSize + sizeof(t_malloc_block *);
		putTypeAndPtr(current->zoneType, current->blockStart);
		if (current->zoneType == 1 || current->zoneType == 2)
		{
			putstr(", "), putnbr(current->emptyPool), putstr("/"), putnbr(current->totalPool);
			putstr(" empty pool of "), putnbr(current->poolSize), putstr(" bytes\n");

			t_malloc_pool *currentPool = current->pool;
			while (currentPool != NULL)
			{
				if (currentPool->isAllocated == true)
				{
					putptr(currentPool->ptr), putstr(" - "), putptr((void *)(currentPool->ptr + currentPool->size));
					putstr(" : "), putnbr(currentPool->size), putstr(" bytes\n");
					totalBytes += currentPool->size;
				}
				currentPool = currentPool->next;
			}
		}
		current = current->next;
	}
	putstr("Total : "), putnbr(totalBytes), putstr(" bytes\n"), putstr("Total allocated : "), putnbr(totalAllocatedBytes), putstr(" bytes\n");
}
