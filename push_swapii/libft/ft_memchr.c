/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:46:02 by dbali             #+#    #+#             */
/*   Updated: 2026/05/05 16:46:04 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;

	str = s;
	while (n > 0)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
		n--;
	}
	return (NULL);
}

/* int	main(void)
{
	char str[] = "hello";
	char c = 'e';

	char *pstr1 = (char *)memchr(str, c, 5);
	printf("func: %s\n", pstr1);
	
	char *pstr2 = (char *)ft_memchr(str, c, 5);
	printf("myfund: %s\n", pstr2);
} */
