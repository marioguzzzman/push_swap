/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:20:23 by dbali             #+#    #+#             */
/*   Updated: 2026/05/05 16:20:25 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*end;

	end = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			end = ((char *)s);
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (end);
}

/* int	main(void)
{
	char str[] = "heeeello";
	char c = 'e';

	printf("func: %s\n", strrchr(str, c));
	printf("myfunc: %s\n", ft_strrchr(str, c));
} */
