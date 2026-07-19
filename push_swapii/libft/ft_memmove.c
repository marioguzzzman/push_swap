/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:27:13 by dbali             #+#    #+#             */
/*   Updated: 2026/05/04 16:27:15 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*pdest;
	const char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = dest;
	psrc = src;
	if (pdest < psrc)
	{
		while (n--)
			*pdest++ = *psrc++;
	}
	else
	{
		pdest = pdest + n - 1;
		psrc = psrc + n - 1;
		while (n--)
			*pdest-- = *psrc--;
	}
	return (dest);
}

/* int	main(void)
{
	char src1[] = "hello world";
	char src2[] = "hello world";
	char dest1[50] = "aaa";

	printf("before: %s\n", src1);
	ft_memmove(dest1, src1, 4);
	printf("after: %s\n", dest1);
	
	memmove(dest1, src1, 4);
	printf("memmove: %s\n", dest1);
} */
