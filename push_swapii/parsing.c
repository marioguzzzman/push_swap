/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:46:46 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 13:54:44 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	is_flag: recognises the 5 flags this program understands.
	arg: one argv token. Returns 1 if it is a known flag, 0 otherwise.
*/
static int	is_flag(const char *arg, t_data *data)
{
	// 
	if (!ft_strlen(arg) || arg[0] != '-' || arg[1] != '-')
		return (0);

	// Match the flags
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
	whitespace into an array of tokens terminated by NULL.
	Used only when the whole number list was passed as one shell argument.
*/
static int	count_tokens(const char *s)
{
	int	count; // How many tokens found so far
	int	in_token; // Flag

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

/*
	split_whitespace: splits one string into an array of strings using whitespaces
*/
static char	**split_whitespace(const char *s)
{
	char	**tokens; // Array of strings returned
	int		count; // number of tokens in the input
	int		t; // index inside tokens array
	size_t	i; // index for the original string
	size_t	j; // index using while copying tokens
	size_t	start; // index where the current token begins

	count = count_tokens(s);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	t = 0;
	i = 0;
	while (s[i]) // Start scanning the string
	{
		while (s[i] && ft_isspace(s[i])) // Skip spaces
			i++;
		start = i;
		while (s[i] && !ft_isspace(s[i])) // Skip spaces
			i++;
		if (i > start) // If i advanced and tokens were found
		{
			tokens[t] = malloc(i - start + 1); // Allocate
			if (tokens[t])
			{
				j = 0;
				while (start + j < i) // Start copying
				{
					tokens[t][j] = s[start + j];
					j++;
				}
				tokens[t][j] = '\0';
			}
			t++;
		}
	}
	tokens[t] = NULL; // End of array
	return (tokens);
}

/*
	token_to_long: converts one already-validated numeric token to a long and
	checks it fits inside an int. Sets *ok to 0 on overflow.
		- ok - flag to detect overflow.
*/
static long	token_to_long(const char *s, int *ok)
{
	long	res; // Result
	int		neg; // Negative number (0 - pos, 1 - neg)
	size_t	i;

	res = 0; // Start at 0
	neg = 0; // Assume the number is positive at first
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		neg = (s[i] == '-');
		i++;
	}
	while (s[i]) // Convert ASCII to number
	{
		res = res * 10 + (s[i] - '0');
		if (res > (long)INT_MAX + 1) // Smallest signed int has one extra value
		{
			*ok = 0; // Conversion failed
			return (0);
		}
		i++;
	}
	if (neg) // if neg was 1
		res = -res;
	if (res < INT_MIN || res > INT_MAX) // Range validation
		*ok = 0;
	return (res);
}

// has_duplicate: scan over the value array and skip duplicates
static int	has_duplicate(long *values, int n)
{
	int	i; // First value
	int	j; // Second value

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
	int		i; // Values index
	t_stack	*node;

	i = n - 1; // Start at the end because stack_add_top() inserts at the beginning of a list
	while (i >= 0) // Continue until every value became a node
	{
		node = malloc(sizeof(t_stack));
		if (!node)
			return (0);
		node->value = values[i]; // Insert value to 'value'
		node->index = 0; // Evry node starts with index 0
		node->next = NULL; // New nodes do not point anywhere yet
		stack_add_top(&data->a, node); // Insert at the top of the stack
		i--;
	}
	return (1);
}

/*
	parse_arguments: main function of this file
	- separates flag tokens from numeric tokens,
	- if exactly one token is given and it contains whitespace or
		the token list is a single combined string, split it further.
	- validates every numeric token and its range,
	- rejects duplicates.
	- builds stack a.
	Returns 1 if success, 0 if there were zero numbers to sort and calls
	exit_error().
*/
int	parse_arguments(int argc, char **argv, t_data *data)
{
	char	**tokens; // Args of numbers
	long	*values; // Stores the converted numeric values
	int		n; // Number of numeric tokens
	int		i;
	int		ok; // Success / failure flag
	int		split_used; // Remember whether split_whitespace() allocated new memory (for "1 2 3"
	char	**split; // Stores the result of split_whitespace()

	data->strategy = "adaptive"; // default
	data->bench = 0; // benchmark disabled by default
	n = 0;
	i = 1;
	while (i < argc) // count how many args are not flags
	{
		if (!is_flag(argv[i], data))
			n++;
		i++;
	}
	if (n == 0) // If no numbers, there is nothing to sort
		return (0);
	tokens = malloc(sizeof(char *) * (n + 1));
	if (!tokens)
		exit_error(data);
	n = 0;
	i = 1;
	while (i < argc) // Store only numeric args
	{
		if (!is_flag(argv[i], data))
			tokens[n++] = argv[i];
		i++;
	}
	tokens[n] = NULL; // Null-terminate the array
	split_used = 0;
	if (n == 1 && count_tokens(tokens[0]) > 1) // Handle quoted input
	{
		split = split_whitespace(tokens[0]); // Crate a new array with numbers
		free(tokens);
		tokens = split;
		split_used = 1; // Split created new strings
		n = 0;
		while (tokens && tokens[n]) // Recalculate token count after splitting
			n++;
	}
	values = malloc(sizeof(long) * n); // for converted numbers
	if (!values)
		exit_error(data);
	i = 0;
	while (i < n) // convert to numbers
	{
		if (!ft_str_is_number(tokens[i]))
			exit_error(data);
		ok = 1;
		values[i] = token_to_long(tokens[i], &ok);
		if (!ok)
			exit_error(data);
		i++;
	}
	if (has_duplicate(values, n)) // Reject duplicates
		exit_error(data); 
	if (!build_stack_from_values(data, values, n)) // Create stack a
		exit_error(data);
	free(values);
	if (split_used) // id split_used = 1
	{
		i = 0;
		while (tokens[i])
			free(tokens[i++]);
	}
	free(tokens);
	return (1);
}
