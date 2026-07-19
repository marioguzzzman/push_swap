/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:49:18 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 11:49:19 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_putnbr_fd(long n, int fd)
{
	char	c;

	if (n < 0)
	{
		ft_putstr_fd("-", fd);
		ft_putnbr_fd(-(n % 10), fd);
		if (n / 10 != 0)
			ft_putnbr_fd(-(n / 10), fd);
		return ;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

/* int main(void)
{
    ft_putnbr_fd(555, 1);
    ft_putchar_fd('\n', 1);
    return (0);
} */
