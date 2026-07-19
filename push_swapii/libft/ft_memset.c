/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:26:18 by dbali             #+#    #+#             */
/*   Updated: 2026/05/04 14:26:19 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n-- > 0)
		*p++ = c;
	return (s);
}

/* int	main(void)
{
	char s[50] = "hello world";
	char s1[50] = "me is cool";

	printf("before: %s\n", s);

	ft_memset(s, 'A', 3);
	
	printf("after: %s\n", s);
	
	memset(s1, 'A', 3);
	printf("memset: %s\n", s1);
} */
