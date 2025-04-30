/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:49:36 by cpapot            #+#    #+#             */
/*   Updated: 2025/04/28 13:21:32 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <bits/mman-linux.h>

void *ft_malloc(size_t size)
{

	
	void *result = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	

	printf("malloc\n");
	return (result);
}
