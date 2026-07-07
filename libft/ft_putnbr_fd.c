/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:50:42 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/20 19:19:29 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln = -ln;
	}
	if (ln >= 10)
		ft_putnbr_fd(ln / 10, fd);
	write(fd, &"0123456789"[ln % 10], 1);
}

/*
DESCRIPTION
Outputs the interger n to a specified file descriptor

NOTE
make sure n does not overflow by using long
Use ft_putnbr_fd as a recursive function that maintains a call stack
that writes and comes back waiting to the deepes recursion to finish
so that the numbers can be printed in the correct order.

int	main(void)
{
int	nb;

nb = -2147483648;
ft_putnbr(nb);
write(1, "\n", 1);
nb = 0;
ft_putnbr(nb);
write(1, "\n", 1);
nb = 10;
ft_putnbr(nb);
write(1, "\n", 1);
nb = 2147483647;
ft_putnbr(nb);
write(1, "\n", 1);
return (0);
}
*/
