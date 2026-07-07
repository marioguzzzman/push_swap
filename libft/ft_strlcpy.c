/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strlcpy.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/05 16:27:23 by maguzman         #+#    #+#              */
/*   Updated: 2026/05/26 21:22:12 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (size == 0)
		return (slen);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (slen);
}

/*
DESCRIPTION
It copies a string with a safety guard of taking the full size of the buffer
and making sure thee is space to NUL-temrinate the result. As long as size > 0.
Important to make sure NUL is included in size and therefore to have size - 1.
It operates in true "c" strings, meaning that they only take
NUL-terminated strings.

RETURN VALUES
It returns the total length of the string they tried to create.
*/
