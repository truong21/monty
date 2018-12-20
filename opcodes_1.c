#include "monty.h"

/**
 * pall - prints all the values on the stack, starting from the top
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
 * push - pushes an element to the top of the stack
 * @stack: pointer to pointer to the top of stack
 * @line_number: line_number of instructions
 * Return: pointer to newly added element
 */
void _push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;
	char *op_num;

	op_num = strtok(NULL, DELIMS);
	if (only_digit(op_num) == TRUE)
	{
		new_node = malloc(sizeof(stack_t));
		if (!new_node)
		{
			dprintf(STDERR_FILENO, "Error: malloc failed\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction push", line_number);
		exit(EXIT_FAILURE);
	}
	new_node->n = atoi(op_num);
	new_node->prev = NULL;
	if (!*stack)
	{
		new_node->next = *stack;
		*stack = new_node;
	}
	else
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
		*stack = new_node;
	}
}
