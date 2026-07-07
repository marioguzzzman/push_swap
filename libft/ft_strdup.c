/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:19:22 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/20 12:28:43 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	size;

	size = ft_strlen(s);
	ptr = malloc(size + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, size + 1);
	return (ptr);
}

/*
DESCRIPTION
The strdup() function returns a pointer to a new string which is a duplicate
of the string s.Memory for the new
string is obtained with malloc(3), and can be freed with free(3).

RETURN VALUE
On	success, the strdup() function returns a pointer to the duplicated string.
It returns NULL if insufficient
memory was available, with errno set to indicate the cause of the error.

** ft_strdup duplicates a string dinamically allocating memory
** Returns a pointer that that can be successfully passed to free()
or NULL if malloc fails to allcoate memory
** Note: remember to add 1 for the null terminator.
*/
