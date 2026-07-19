/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:01:25 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 15:47:57 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

void	ft_bzero(void *s, size_t n)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

/* int main(void)
{
	char str[20] = "hello world";
	char str2[20] = "me is cool";

	printf("before: %s\n", str);

	ft_bzero(str, 3);

	printf("after:  %s\n", str);
	
	bzero(str2, 3);
	printf("bzero: %s\n", str2);
	
	
	for (int i = 0; i < 5; i++)
		printf("%d\n", str[i]);
} */
