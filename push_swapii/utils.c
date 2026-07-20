/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:40:37 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 17:16:22 by maguzman         ###   ########.fr       */
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
	put_str_fd: const-correct front-end to libft's ft_putstr_fd.
	The strings this program prints (strategy names, complexity labels) are
	string literals, so t_data holds them as const char * — writing through
	such a pointer is undefined behaviour and the const makes the compiler
	enforce that. libft predates const-correctness and declares
	ft_putstr_fd(char *, int) even though it never modifies the string, so
	the cast is unavoidable; it is isolated here rather than repeated at
	every call site.
*/
void	put_str_fd(const char *s, int fd)
{
	ft_putstr_fd((char *)s, fd);
}

/*
	ft_putnbr_double_fd: writes a double with two decimal
	digits (0.11, 100.00). Used disorder.
*/
void	ft_putnbr_double_fd(double n, int fd)
{
	long	int_part;
	long	frac_part;

	if (n < 0)
		n = 0;
	int_part = (long)n;
	frac_part = (long)((n - (double)int_part) * 100 + 0.5);
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
