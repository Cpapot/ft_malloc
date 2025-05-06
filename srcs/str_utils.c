/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:04:16 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/06 23:30:41 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/str_utils.h"

size_t strlen(const char *str)
{
	size_t		i;

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

void puthexadecimal(unsigned int nbr)
{
	char	str[12];
	int		i;

	i = 0;
	if (nbr == 0)
	{
		putstr("00");
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
	if (i == 1)
		putstr("0");
	while (--i >= 0)
		write(1, &str[i], 1);
}

void puthexadump(void *ptr, size_t size)
{
	unsigned char	*bytePtr = (unsigned char *)ptr;
	size_t			i;
	const size_t	maxSize = 799;

	for (i = 0; i < size && i < maxSize; i++)
	{
		if (i % 16 == 0 && i != 0)
			putstr("\n");
		puthexadecimal(bytePtr[i]);
		putstr(" ");
	}
	if (size > maxSize)
		putstr("...");
	putstr("\n");
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
