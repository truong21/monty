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
		dprintf(STDERR_FILENO,"Usage: monty file\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	read_file(filename, &head);
	return (EXIT_SUCCESS);
}
