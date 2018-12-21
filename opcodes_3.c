#include "monty.h"

/**
 * _mod - mod the second top element of the stack by the top element
 * of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _mod(stack_t **stack, unsigned int line_number)
{
	if (!*stack || !((*stack)->next))
	{
		dprintf(STDERR_FILENO, "L%u: can't mod, stack too short\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%u: division by zero\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n %= (*stack)->n;
	_pop(stack, line_number);
}
/**
 * _pchar - prints the char at the top of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _pchar(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	if (((*stack)->n > 64 && (*stack)->n < 91) ||
		((*stack)->n > 96 && (*stack)->n < 123))
	{
		putchar((*stack)->n);
		putchar('\n');
	}
	else
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, value out of range\n",
									line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}
/**
 * _pstr - prints the string starting at the top of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	(void)line_number;
	if (!stack || !*stack)
	{
		printf("\n");
		return;
	}
	tmp = *stack;
	while (tmp)
	{
		if (tmp->n == 0)
			break;
		if ((tmp->n > 64 && tmp->n < 91) ||
			(tmp->n > 96 && tmp->n < 123))
		{
			putchar(tmp->n);
		}
		else
			break;
		tmp = tmp->next;
	}
	printf("\n");
}
/**
 * _rotl - rotates the stack to the top (top element becomes last and second
 * elements becomes the first one
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *top;
	(void)line_number;

	if (!*stack || !(*stack)->next)
		return;
	tmp = *stack;
	top = (*stack)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	(*stack)->next = NULL;
	*stack = top;
}
/**
 * _rotr - rotates the stack to the bottom (top element becomes second and
 * bottom element becomes the first one
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	(void)line_number;

	if (!*stack || !(*stack)->next)
		return;
	tmp = *stack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->prev->next = NULL;
	tmp->next = *stack;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	*stack = tmp;
}
