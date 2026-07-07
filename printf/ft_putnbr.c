/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 16:49:22 by maguzman          #+#    #+#             */
/*   Updated: 2026/06/19 19:09:10 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	ln;
	int		count;

	count = 0;
	ln = n;
	if (ln < 0)
	{
		write(1, "-", 1);
		count += 1;
		ln = -ln;
	}
	if (ln >= 10)
		count += ft_putnbr(ln / 10);
	count += write(1, &"0123456789"[ln % 10], 1);
	return (count);
}
