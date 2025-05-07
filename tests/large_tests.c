/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:03:31 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/07 17:03:41 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "../libft/includes/libft.h"

void safe_print(const char *str)
{
	write(1, str, strlen(str));
}

int main()
{
	
}
