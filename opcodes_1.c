#include "monty.h"

/**
 * _pall - prints all the values on the stack, starting from the top
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 * Return: Nothing
 */
void _pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	(void)line_number;

	tmp = *stack;
	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
/**
 * _push - pushes an element to the top of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 * Return: pointer to newly added element
 */
void _push(stack_t **stack, unsigned int line_number)
{
	if (glob.queue == 0)
		_push_stack(stack, line_number);
	else
		_push_queue(stack, line_number);
}
/**
 * _pint - prints the value at the top of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _pint(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
 * _pop - removes the top element of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!stack || !*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
}
/**
 * _swap - swaps the top two element of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!*stack || !((*stack)->next))
	{
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	if (tmp->next)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack) = tmp;
}
