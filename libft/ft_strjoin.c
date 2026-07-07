/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:33:55 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/20 13:21:27 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc((s1_len + s2_len) + 1);
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, s1_len + 1);
	ft_strlcpy(s3 + s1_len, s2, s2_len + 1);
	return (s3);
}

/*
DESCRIPTION
It it concatenates 2 strings, s1 as prefix and s2 as sufix.

RETURN VALUES
Returns a new string that is the concatenation of both.
NULL if the allocation failed.

NOTES
the + 1 tells strlcpy the true buffer size
so it knows where it's safe to write the null terminator
and not to overwrite beyond the buffer.
*/
