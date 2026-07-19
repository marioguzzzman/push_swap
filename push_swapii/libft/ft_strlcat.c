/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:40:51 by dbali             #+#    #+#             */
/*   Updated: 2026/05/14 11:56:54 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	d;
	unsigned int	s;
	unsigned int	i;

	d = ft_strlen((char *)dst);
	s = ft_strlen((char *)src);
	i = 0;
	if (size <= d)
		return (size + s);
	while (src[i] != '\0' && (d + i) < (size - 1))
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (d + s);
}

/* int	main(void)
{
	char dest[5] = "hello";
	char src[5] = "world";

	printf("Dest Before: %s\n", dest);
	printf("Return of strlcat: %zu\n", ft_strlcat(dest, src, 50));
	printf("Dest after: %s\n", dest);
} */
