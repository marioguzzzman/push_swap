/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:29:04 by dbali             #+#    #+#             */
/*   Updated: 2026/05/04 15:29:05 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	while (n--)
		*pdest++ = *psrc++;
	return (dest);
}

/* int	main(void)
{
	char src[] = "hello world";
	char dest1[50];
	char dest2[50];

	printf("before: %s\n", src);
	
	ft_memcpy(dest1, src, sizeof(src));
	
	printf("after: %s\n", dest1);
	
	memcpy(dest2, src, sizeof(src));
	
	printf("memcpy: %s\n", dest2);
} */
