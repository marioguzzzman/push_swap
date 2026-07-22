/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 13:01:09 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/22 18:34:34 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

/*
count_tokens: split a single string (ex: "3 1 2") on
whitespace into an array of mallocated tokens terminated by NULL.
Used only when the whole number list was passed as one shell argument.
*/

int	count_tokens(const char *s)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && !in_token)
		{
			in_token = 1;
			count++;
		}
		else if (ft_isspace(*s))
			in_token = 0;
		s++;
	}
	return (count);
}

char	**split_whitespace(const char *s)
{
	char	**tokens;
	int		count;
	int		t;
	size_t	i;
	size_t	j;
	size_t	start;

	count = count_tokens(s);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	t = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		start = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		if (i > start)
		{
			tokens[t] = malloc(i - start + 1);
			if (tokens[t])
			{
				j = 0;
				while (start + j < i)
				{
					tokens[t][j] = s[start + j];
					j++;
				}
				tokens[t][j] = '\0';
			}
			t++;
		}
	}
	tokens[t] = NULL;
	return (tokens);
}

/*
token_to_long: converts one already-validated numeric token to a long and
checks it fits inside an int. Sets *ok to 0 on overflow.
*/

long	token_to_long(const char *s, int *ok)
{
	long	res;
	int		neg;
	size_t	i;

	res = 0;
	neg = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		neg = (s[i] == '-');
		i++;
	}
	while (s[i])
	{
		res = res * 10 + (s[i] - '0');
		if (res > (long) INT_MAX + 1)
		{
			*ok = 0;
			return (0);
		}
		i++;
	}
	if (neg)
		res = -res;
	if (res < INT_MIN || res > INT_MAX)
		*ok = 0;
	return (res);
}

char	**split_needed(int *n, char **tokens)
{
	char	**split;
	int		n_local;

	n_local = *n;
	if (n_local == 1 && count_tokens(tokens[0]) > 1)
	{
		split = split_whitespace(tokens[0]);
		free(tokens);
		tokens = split;
		n_local = 0;
		while (tokens && tokens[n_local])
			n_local++;
	}
	*n = n_local;
	return (tokens);
}

char	**collect_tokens(int *n, int argc, char **argv, t_data *data)
{
	char	**tokens;
	int		i;
	int		n_local;

	i = 1;
	n_local = *n;
	while (i < argc)
	{
		if (!is_flag(argv[i], data))
			n_local++;
		i++;
	}
	tokens = malloc(sizeof(char *) * (n_local + 1));
	if (!tokens)
		exit_error(data);
	n_local = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i], data))
			tokens[n_local++] = argv[i];
		i++;
	}
	tokens[n_local] = NULL;
	tokens = split_needed(&n_local, tokens);
	*n = n_local;
	return (tokens);
}
