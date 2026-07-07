/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_memset.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/30 12:40:40 by maguzman         #+#    #+#              */
/*   Updated: 2026/04/30 22:29:22 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	int				i;
	unsigned char	*s;

	s = (unsigned char *) str;
	i = 0;
	while (n > 0)
	{
		s[i] = (unsigned char) c;
		i++;
		n--;
	}
	return (s);
}
