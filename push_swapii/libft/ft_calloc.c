/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:51:45 by dbali             #+#    #+#             */
/*   Updated: 2026/05/13 11:32:12 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	sum;
	void	*ptr;

	sum = nmemb * size;
	ptr = malloc(sum);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, sum);
	return (ptr);
}

/* int	main(void)
{
	int	*arr;
	int	i;

	arr = ft_calloc(3, sizeof(int));
	if (!arr)
		return (1);
	i = 0;
	while (i < 5)
	{
		printf("%d ", arr[i]);
		i++;
	}
	free(arr);
	return (0);
} */

// Real func
/* int	main(void)
{
	int	*arr;
	int	i;

	arr = calloc(3, sizeof(int));
	if (!arr)
		return (1);
	i = 0;
	while (i < 5)
	{
		printf("%d ", arr[i]);
		i++;
	}
	free(arr);
	return (0);
} */
