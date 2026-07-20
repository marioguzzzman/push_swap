/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:31:46 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 15:33:28 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// stack_add_top: pushes an already-allocated node onto the top of *stack
void	stack_add_top(t_stack **stack, t_stack *new_node)
{
	new_node->next = *stack;
	*stack = new_node;
}

// stack_pop_top:
// detaches and returns the top node of *stack (NULL if empty)
t_stack	*stack_pop_top(t_stack **stack)
{
	t_stack	*top;

	if (!stack || !*stack)
		return (NULL);
	top = *stack;
	*stack = (*stack)->next;
	top->next = NULL;
	return (top);
}

// free_stack: frees every node of *stack and resets it to NULL
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (stack && *stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
