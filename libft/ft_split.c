/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_split.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/22 14:34:33 by maguzman         #+#    #+#              */
/*   Updated: 2026/05/26 18:37:02 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c);
static int	get_words(char const *s, char c, char **array);
static void	free_array(char **array);
static int	add_word(char const *s, char c, int *i);

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		get_word_check;

	if (s == NULL)
		return (NULL);
	array = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (array == NULL)
		return (NULL);
	get_word_check = get_words(s, c, array);
	if (get_word_check == 1)
	{
		free(array);
		return (NULL);
	}
	else
		return (array);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	word_count;
	int	in_word;

	i = 0;
	word_count = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			if (in_word == 0)
			{
				word_count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (word_count);
}

static void	free_array(char **array)
{
	int	j;

	j = 0;
	while (array[j] != NULL)
	{
		free(array[j]);
		j++;
	}
}

static int	add_word(char const *s, char c, int *i)
{
	int	len;

	len = 0;
	while (s[*i] != c && s[*i] != '\0')
	{
		len++;
		(*i)++;
	}
	return (len);
}

static int	get_words(char const *s, char c, char **array)
{
	int	i;
	int	j;
	int	start;
	int	len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			len = add_word(s, c, &i);
			array[j++] = ft_substr(s, start, len);
			if (array[j - 1] == NULL)
			{
				free_array(array);
				return (1);
			}
		}
		else
			i++;
	}
	array[j] = NULL;
	return (0);
}

/*
DESCRIPTION
Allocates memory (using malloc(3)) and returns an
array of strings obtained by splitting ’s’ using
the character ’c’ as a delimiter.
Each string in the returned array is allocated
independently.
The array of pointers itself is also allocated
dynamically.
The returned array must be NULL terminated.

PARAMET
*/
