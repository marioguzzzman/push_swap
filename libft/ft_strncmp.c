/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_strncmp.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/24 11:00:43 by maguzman         #+#    #+#              */
/*   Updated: 2026/05/26 17:27:18 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
/*
int	main(void)
{
char	*s1;
char	*s2;
int		n;

n = 5;
s1 = "hello";
s2 = "hello";
printf("should be 0 %d\n", ft_strncmp(s1, s2, n));
s1 = "hellworldo";
s2 = "hell o";
printf("should be positive %d\n", ft_strncmp(s1, s2, n));
s1 = "halla";
s2 = "hellohello";
printf("should be negative %d\n", ft_strncmp(s1, s2, n));

return (0);
}*/
