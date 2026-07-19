/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:27:18 by dbali             #+#    #+#             */
/*   Updated: 2026/05/14 13:08:47 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static int	count_chars_needed(long number)
{
	int	count;

	count = 0;
	if (number <= 0)
	{
		number *= -1;
		count++;
	}
	while (number > 0)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

static char	*fill_string(char *result, long number, int last_index)
{
	if (number == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (number < 0)
	{
		result[0] = '-';
		number = number * -1;
	}
	while (number > 0)
	{
		result[last_index] = (number % 10) + '0';
		number = number / 10;
		last_index--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*str_result;
	int		str_length;
	long	number;

	number = n;
	str_length = count_chars_needed(number);
	str_result = (char *)malloc(sizeof(char) * (str_length + 1));
	if (!str_result)
		return (NULL);
	str_result[str_length] = '\0';
	return (fill_string(str_result, number, str_length - 1));
}

/* int main()
{
    int number = -42;
    char *result = ft_itoa(number);
    printf("The string representation of %d is: %s\n", number, result);
    free(result);
    return 0;
} */
