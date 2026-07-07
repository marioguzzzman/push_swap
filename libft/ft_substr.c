/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:56:25 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/20 12:25:16 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	copy_len;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		ptr = malloc(1);
		if (ptr == NULL)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (s_len - start < len)
		copy_len = s_len - start;
	else
		copy_len = len;
	ptr = malloc(copy_len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s + start, copy_len + 1);
	return (ptr);
}

/*
DESCRIPTION
Allocates memory and returns a substring from S.
The substring starts at index start and has a max length of len

RETURN VALUES
The substring and NULL if the allocation fails

NOTES
Allocate an extra byte to strlcpy to make space for the NULL
Important to calculate an actual possible lenght of the copy
to avoid allocating more memory than necesary or undefined behaviors.
*/
