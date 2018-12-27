#include "monty.h"

/**
 * read_file - reads line from file and executes the instructions
 * @filename: name of file
 * @stack: stack
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
void read_file(const char *filename, stack_t **stack)
{
	FILE *file;
	char *op = NULL, *line = NULL;
	size_t size;
	int line_number = 0;

	if (!filename)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	glob.fp = file = fopen(filename, "r");
	if (!file)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &size, file) != -1)
	{
		glob.buf = line;
		line_number++;
		op = strtok(line, DELIMS);
		if (op == NULL || op[0] == '#')
			continue;
		if (op)
			execute_op(stack, op, line_number);
	}
}
/**
 * execute_op - execute the opcode
 * @stack: stack
 * @op: opcode
 * @line_number: line number of instruction
 */
void execute_op(stack_t **stack, char *op, unsigned int line_number)
{
	int i;

	instruction_t ops[] = {
		{"push", _push}, {"pall", _pall},
		{"pint", _pint}, {"pop", _pop},
		{"swap", _swap}, {"add", _add},
		{"nop", _nop}, {"sub", _sub},
		{"div", _div}, {"mul", _mul},
		{"mod", _mod}, {"pchar", _pchar},
		{"pstr", _pstr}, {"rotl", _rotl},
		{"rotr", _rotr}, {NULL, NULL},
	};
	for (i = 0; ops[i].opcode; i++)
	{
		if (strcmp(op, ops[i].opcode) == 0)
		{
			ops[i].f(stack, line_number);
			return;
		}
	}
	if (strcmp(op, "stack") == 0)
	{
		glob.queue = 0;
		return;
	}
	else if (strcmp(op, "queue") == 0)
	{
		glob.queue = 1;
		return;
	}
	if (strlen(op) != 0 && op[0] != '#')
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n", line_number, op);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
}
/**
 * only_digit - check if every character in a string is a digit
 * @num: string to check
 * Return: True or False
 */
int only_digit(char *num)
{
	int i = 0;

	if (!num)
		return (FALSE);
	if (num[0] == '-')
		i++;
	for (; num[i] != '\0'; i++)
	{
		if (isdigit(num[i]) == FALSE)
			return (FALSE);
	}

	return (TRUE);
}
/**
 * _push_stack - push new node into stack
 * @stack: pointer to ponter to the stack
 * @line_number: line number of the instruction file
 */
void _push_stack(stack_t **stack, unsigned int line_number)
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
			free_stack(stack);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		free_stack(stack);
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
/**
 * _push_queue - adds a new node at the end of a dlistint_t list
 * @stack: pointer to pointer to stack
 * @line_number: line number of the instruction file
 */
void _push_queue(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node, *tmp;
	char *op_num;

	op_num = strtok(NULL, DELIMS);
	if (only_digit(op_num) == TRUE)
	{
		new_node = malloc(sizeof(stack_t));
		if (!new_node)
		{
			dprintf(STDERR_FILENO, "Error: malloc failed\n");
			free_stack(stack);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	new_node->n = atoi(op_num);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*stack == NULL)
		*stack = new_node;
	else
	{
		tmp = *stack;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new_node->prev = tmp;
		tmp->next = new_node;
	}
}
