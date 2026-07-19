/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:59:39 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 10:59:46 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
	{
		substr = (char *)malloc(sizeof(char) * 1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > s_len - start) 
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

/* int main(void)
{
    printf("substr1 (success): %s\n", ft_substr("helloworld", 5, 5));
    printf("substr1 (null): %s\n", ft_substr("helloworld", 30, 5));
    printf("substr2 (len > s_len): %s\n", ft_substr("helloworld", 7, 30));
    free(ft_substr("helloworld", 5, 5));
    free(ft_substr("helloworld", 30, 5));
    free(ft_substr("helloworld", 7, 30));
    return (0);
} */
