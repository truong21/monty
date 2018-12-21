#include "monty.h"

/**
 * _add - adds the top two elements of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _add(stack_t **stack, unsigned int line_number)
{
	if(!*stack || !((*stack)->next))
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
		free_stack();
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n += (*stack)->n;
	_pop(stack, line_number);
}
/**
 * _nop - do nothing
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 */
void _nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
