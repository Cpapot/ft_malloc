/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:52 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/06 22:58:51 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_UTILS_H
# define STR_UTILS_H

# include <unistd.h>

size_t		strlen(const char *str);
void		putstr(char *str);
void		putnbr(unsigned int nbr);
void		putptr(void *ptr);
void		putTypeAndPtr(int type, void *ptr);
void		puthexadump(void *ptr, size_t size);


#endif
