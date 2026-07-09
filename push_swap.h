/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.h                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/04 16:51:52 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/09 16:46:50 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	int				size;
	struct s_node	*top;
	struct s_node	*bottom;
}	t_stack;

/* STACK */
t_stack	*init_stack(void);

/* NODES */
t_node	*create_node(int value);
void	stack_add_bottom(t_stack *s, t_node *node);

/* PARSING */
void	push_swap(t_stack *stack);
long	*get_numbers(char *argv, int *count);

/* ALGORITHMS */
double	disorder_calculation(long *arr_numbers, int numbers_len);

#endif
