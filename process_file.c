#include "monty.h"

/**
 * read_file - reads line from file and executes the instructions
 * filename: name of file
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
void read_file(const char *filename, stack_t **stack)
{
	FILE *file;
	char *line;
	char *op = NULL;
	size_t size = 0;
	int line_number = 0, read = 0;

	line = NULL;
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
	while ((read = getline(&line, &size, file)) != -1)
	{
		op = strtok(line, DELIMS);
		line_number++;
		if (op)
			execute_op(stack, op, line_number);
	}
	free(line);
	fclose(file);
}

void execute_op(stack_t **stack, char *op, unsigned int line_number)
{
	int i;

	instruction_t ops[] = {
		{"push", _push},
		{"pall", _pall},
		{NULL, NULL},
	};
	for (i = 0; ops[i].opcode; i++)
	{
		if (strcmp(op, ops[i].opcode) == 0)
		{
			ops[i].f(stack, line_number);
			return;
		}
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
	for(i = 0; num[i] != '\0'; i++)
	{
		if (isdigit(num[i]) == FALSE)
			return (FALSE);
	}

	return (TRUE);
}
