/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:48:49 by dbali             #+#    #+#             */
/*   Updated: 2026/05/14 10:40:01 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*pstr1;
	const unsigned char	*pstr2;

	pstr1 = s1;
	pstr2 = s2;
	while (n--)
	{
		if (*pstr1 != *pstr2)
			return (*pstr1 - *pstr2);
		pstr1++;
		pstr2++;
	}
	return (0);
}

/* int	main(void)
{
	char str1[] = "123";
	char str2[] = "123";

	printf("func: %d\n", memcmp(str1, str2, 2));
	printf("myfunc: %d\n", ft_memcmp(str1, str2, 2));
} */