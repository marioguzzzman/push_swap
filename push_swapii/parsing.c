/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parsing.c                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/13 13:46:46 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/23 12:14:40 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

/*
is_flag: recognises the 5 optional flags this program understands.
arg: one argv token. Returns 1 if it is a known flag, 0 otherwise.
*/

int	is_flag(const char *arg, t_data *data)
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

	data->strategy = "adaptive";
	data->bench = 0;
	n = 0;
	tokens = collect_tokens(&n, argc, argv, data);
	if (n == 0)
		return (0);
	values = malloc(sizeof(long) * n);
	if (!values)
		exit_error(data);
	if (validate(n, values, tokens))
		exit_error(data);
	if (has_duplicate(values, n))
		exit_error(data);
	if (!build_stack_from_values(data, values, n))
		exit_error(data);
	free(values);
	free(tokens);
	return (1);
}
