#include "monty.h"

glob_t glob = {NULL, NULL, NULL, 0};
/**
 * free_stack - free all malloc'ed memory of the stack
 * @stack: pointer to pointer to stack
 */
void free_stack(stack_t **stack)
{
	stack_t *tmp1, *tmp2;

	tmp1 = *stack;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
	if (glob.buf != NULL)
		free(glob.buf);
	fclose(glob.fp);
}
/**
 * main - interpret monty byte code files
 * @argc: argument count
 * @argv: array of strings containing the arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	char *filename;
	stack_t *head = NULL;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	read_file(filename, &head);
	free_stack(&head);
	return (EXIT_SUCCESS);
}
