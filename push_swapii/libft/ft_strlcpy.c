/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:26:47 by dbali             #+#    #+#             */
/*   Updated: 2026/05/05 11:26:48 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	src_length;
	unsigned int	i;

	src_length = 0;
	while (src[src_length] != '\0')
		src_length++;
	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_length);
}

/* int main(void)
{
	char src[] = "I love green";
	char dest[50];
	
	ft_strlcpy(dest, src, 50);
	printf("src: %s\n", src);
	printf("dest: %s (copy)", dest);
} */
