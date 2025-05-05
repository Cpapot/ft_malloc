/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:15:44 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/05 18:25:20 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

int	find_zone_type(size_t size)
{
	if (size == 0)
		return EMPTY;
	else if (size <= n)
		return TINY;
	else if (size <= m)
		return SMALL;
	else
		return LARGE;
}

size_t get_zone_size(int type, size_t size)
{
	//size_t	page_size = getpagesize();

	if (type == TINY)
		return N + (N / n) * sizeof(t_malloc_pool);
	else if (type == SMALL)
		return M + (M / m) * sizeof(t_malloc_pool);
	else
		return size;
}
