/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:46:46 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 12:06:58 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

/*
	is_flag: recognises the 5 optional flags this program understands.
	arg: one argv token. Returns 1 if it is a known flag, 0 otherwise.
*/
static int	is_flag(const char *arg, t_data *data)
{
	if (!ft_strlen(arg) || arg[0] != '-' || arg[1] != '-')
		return (0);
	if (ft_strlen(arg) == 8 && !ft_strncmp_local(arg, "--simple"))
		data->strategy = "simple";
	else if (ft_strlen(arg) == 8 && !ft_strncmp_local(arg, "--medium"))
		data->strategy = "medium";
	else if (ft_strlen(arg) == 9 && !ft_strncmp_local(arg, "--complex"))
		data->strategy = "complex";
	else if (ft_strlen(arg) == 10 && !ft_strncmp_local(arg, "--adaptive"))
		data->strategy = "adaptive";
	else if (ft_strlen(arg) == 7 && !ft_strncmp_local(arg, "--bench"))
		data->bench = 1;
	else
		return (0);
	return (1);
}

// ft_strncmp_local: strcmp replacement
int	ft_strncmp_local(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] && b[i])
	{
		if (a[i] != b[i])
			return (1);
		i++;
	}
	return (a[i] != b[i]);
}

/*
	count_tokens: split a single string (ex: "3 1 2") on
	whitespace into an array of mallocated tokens terminated by NULL.
	Used only when the whole number list was passed as one shell argument.
*/
static int	count_tokens(const char *s)
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

static char	**split_whitespace(const char *s)
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
static long	token_to_long(const char *s, int *ok)
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
		if (res > (long)INT_MAX + 1)
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

// has_duplicate: scan over the not-yet-linked value array
static int	has_duplicate(long *values, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (values[i] == values[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
	build_stack_from_values: allocates one t_stack node per value and links
	them so the first value given becomes the TOP of stack a.
*/
static int	build_stack_from_values(t_data *data, long *values, int n)
{
	int		i;
	t_stack	*node;

	i = n - 1;
	while (i >= 0)
	{
		node = malloc(sizeof(t_stack));
		if (!node)
			return (0);
		node->value = values[i];
		node->index = 0;
		node->next = NULL;
		stack_add_top(&data->a, node);
		i--;
	}
	return (1);
}

/*
	parse_arguments: main function of this file
	- separates flag tokens from numeric tokens,
	- if exactly one non-flag token is given and it contains whitespace or
		the token list is a single combined string, splits it further,
	- validates every numeric token and its range,
	- rejects duplicates,
	- builds stack a.
	Returns 1 if success, 0 if there were zero numbers to sort and calls
	exit_error() directly
*/
int	parse_arguments(int argc, char **argv, t_data *data)
{
	char	**tokens;
	long	*values;
	int		n;
	int		i;
	int		ok;
	int		split_used;
	char	**split;

	data->strategy = "adaptive";
	data->bench = 0;
	n = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i], data))
			n++;
		i++;
	}
	if (n == 0)
		return (0);
	tokens = malloc(sizeof(char *) * (n + 1));
	if (!tokens)
		exit_error(data);
	n = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i], data))
			tokens[n++] = argv[i];
		i++;
	}
	tokens[n] = NULL;
	split_used = 0;
	if (n == 1 && count_tokens(tokens[0]) > 1)
	{
		split = split_whitespace(tokens[0]);
		free(tokens);
		tokens = split;
		split_used = 1;
		n = 0;
		while (tokens && tokens[n])
			n++;
	}
	values = malloc(sizeof(long) * n);
	if (!values)
		exit_error(data);
	i = 0;
	while (i < n)
	{
		if (!ft_str_is_number(tokens[i]))
			exit_error(data);
		ok = 1;
		values[i] = token_to_long(tokens[i], &ok);
		if (!ok)
			exit_error(data);
		i++;
	}
	if (has_duplicate(values, n))
		exit_error(data);
	if (!build_stack_from_values(data, values, n))
		exit_error(data);
	free(values);
	if (split_used)
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
	}
	free(tokens);
	return (1);
}
