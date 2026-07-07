/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:24:45 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/20 17:52:27 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_s;
	size_t	trimmed_s_len;
	size_t	start;
	size_t	end;

	trimmed_s_len = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]))
		start++;
	while (end > 0 && ft_strchr(set, s1[end - 1]))
		end--;
	if (start >= end)
		trimmed_s_len = 0;
	else
		trimmed_s_len = end - start;
	trimmed_s = malloc(trimmed_s_len + 1);
	if (trimmed_s == NULL)
		return (NULL);
	ft_strlcpy(trimmed_s, s1 + start, trimmed_s_len + 1);
	return (trimmed_s);
}

/*
DESCRIPTION
Allocates memory and returns a copy of s1
without the char indicated by a set string from the beginning
and the end

RETURNED VALUE
Trimmed string
NULL if allocation fails

NOTE
Guarding this is a bit tricky. Some cases:
1. what happens if the whole s1 is filled with set to remove?
end will be 0 and the start will go to the end.
We need to make sure we protect for integer underflow, so we add end > 0
2. we want ft_strchr(set, s1[start]) to move asking is s1[i] part of set?
if yes, move.
3. What happens if set is "" and empty string?
This is already protected by strchr and returns NULL
*/
