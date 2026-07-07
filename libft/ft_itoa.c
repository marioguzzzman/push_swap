/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 20:02:08 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/23 22:46:01 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long int ln);

static void	fill_digit(char *ascii, long ln, int len, int sign);

char	*ft_itoa(int n)
{
	long	ln;
	int		sign;
	char	*ascii;
	int		len;

	ln = n;
	sign = 0;
	len = 0;
	if (ln < 0)
	{
		ln = -ln;
		sign = 1;
	}
	len = count_digits(ln);
	ascii = malloc(sizeof(char) * (len + sign + 1));
	if (ascii == NULL)
		return (NULL);
	fill_digit(ascii, ln, len, sign);
	return (ascii);
}

static int	count_digits(long int ln)
{
	int	len;

	len = 0;
	while (ln > 0)
	{
		ln = ln / 10;
		len++;
	}
	if (len == 0)
		len = 1;
	return (len);
}

static void	fill_digit(char *ascii, long ln, int len, int sign)
{
	ascii[len + sign] = '\0';
	while (len > 0)
	{
		ascii[len - 1 + sign] = (ln % 10) + '0';
		ln = ln / 10;
		len--;
	}
	if (sign == 1)
		ascii[0] = '-';
}

/*
DESCRIPTION
Allocates memory (using malloc(3)) and returns
a string representing the integer received as an
argument. Negative numbers must be handled.

RETURN VALUE
The string representing the integer.
NULL if the allocation fails.

*/
