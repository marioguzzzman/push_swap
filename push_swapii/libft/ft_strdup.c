/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:55:46 by dbali             #+#    #+#             */
/*   Updated: 2026/05/06 13:55:50 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_strdup(const char *s)
{
	int		i;
	int		length;
	char	*target;

	length = 0;
	while (s[length])
		length++;
	target = (char *) malloc(sizeof(char) * (length + 1));
	if (target == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		target[i] = s[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}

/* int	main(void)
{
	char	str[] = "hello";
	printf("myfunc: %s\n", ft_strdup(str));
	printf("strdup: %s\n", strdup(str));
} */
