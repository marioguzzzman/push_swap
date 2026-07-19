/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:05:41 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 11:05:43 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len_s1);
	ft_memcpy(new_str + len_s1, s2, len_s2);
	new_str[len_s1 + len_s2] = '\0';
	return (new_str);
}

/* int main(void)
{
    char *s1 = "hello ";
    char *s2 = "world";
    char *result = ft_strjoin(s1, s2);
    printf("%s\n", result);
    free(result);
    return (0);
} */
