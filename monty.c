#include "monty.h"

glob_t glob;
/**
 * stack_int - initialize the stack
 * @head: head of stack
 */
void stack_int(stack_t **head)
{
	*head = NULL;
	glob.top = head;
	glob.buf = NULL;
}
/**
 * free_stack - free all malloc'ed memory of the stack
 */
void free_stack(void)
{
	stack_t *tmp1, *tmp2;

	tmp1 = *(glob.top);
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
	if (glob.buf != NULL)
		free(glob.buf);
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
	stack_t *head;

	stack_int(&head);
	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: monty file\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	read_file(filename, &head);
	exit(EXIT_SUCCESS);
}
