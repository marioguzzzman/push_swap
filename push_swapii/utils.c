/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:40:37 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 13:44:46 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

// ft_strlen: returns the number of characters in s, not counting '\0'

// ft_isdigit: 1 if c is a decimal digit ('0'-'9'), 0 otherwise

// ft_putstr_fd: writes the whole null-terminated string s to file descriptor fd

// ft_putnbr_fd: writes the signed number n (as base-10 text) to fd

// ft_isspace: 1 if c is a space or tab (the separators we accept), else 0.
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
	ft_putnbr_double_fd: writes a double with two decimal
	digits (0.11, 100.00). Used disorder.
*/
void	ft_putnbr_double_fd(double n, int fd)
{
	long	int_part;
	long	frac_part;

	if (n < 0) // Disorder = 0-1
		n = 0;
	int_part = (long)n;

	// (n - int_part) - keep what after the decimal point
	// *100 - shift the decimal point 2 digits
	// +0.5 - round to the nearest int
	// Example: (long)42.24 = 42
	//			0.4224 => frac_part = 42
	frac_part = (long)((n - (double)int_part) * 100 + 0.5);

	// Example: 2.999 -> int_part = 2, frac_part = 100 (wrong)
	//			Solution: frac_part = 0 and int_part = 3
	if (frac_part >= 100)
	{
		frac_part -= 100;
		int_part += 1;
	}
	ft_putnbr_fd(int_part, fd);
	ft_putstr_fd(".", fd);
	if (frac_part < 10)
		ft_putstr_fd("0", fd);
	ft_putnbr_fd(frac_part, fd);
}

/*
	t_str_is_number: checks whether the whole string s is a valid
	integer. Returns 1 if valid, 0 otherwise.
*/
int	ft_str_is_number(const char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
