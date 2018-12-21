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
		dprintf(STDERR_FILENO, "Error: Can't open file, %s\n", filename);
		exit(EXIT_FAILURE);
	}
	file = fopen(filename, "r");
	if (!file)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file, %s\n", filename);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &size, file) != -1)
	{
		glob->buf = line;
		line_number++;
		op = strtok(line, DELIMS);
		if (op == NULL || op[0] == '#')
			continue;
		if (op)
			execute_op(stack, op, line_number);
	}
	fclose(file);
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
		{"nop", _nop}, {NULL, NULL},
	};
	for (i = 0; ops[i].opcode; i++)
	{
		if (strcmp(op, ops[i].opcode) == 0)
		{
			ops[i].f(stack, line_number);
			return;
		}
	}
	if (strlen(op) != 0 && op[0] != '#')
	{
		dprintf("l%u: unknown instruction %s\n", line_number, op);
		free_stack();
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
	int i;

	if (!num)
		return (FALSE);
	for (i = 0; num[i] != '\0'; i++)
	{
		if (isdigit(num[i]) == FALSE)
			return (FALSE);
	}

	return (TRUE);
}
