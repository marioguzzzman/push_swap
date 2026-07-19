/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:35:00 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 11:35:51 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

/* char test_function_f(unsigned int i, char c)
{
    if (c>= 'a' && c <= 'z')
        return (c - 32);
    return (c);
} */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	length;
	size_t	i;
	char	*result;

	if (!s || !f)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	while (i < length)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/* int main(void)
{
    char *str = "hello world";
    char *result = ft_strmapi(str, test_function_f);
    printf("str: %s\n", str);
    printf("result: %s\n", result);
    free(result);
    return (0);
} */