#ifndef MONTY_H
#define MONTY_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define DELIMS "\t\n "
#define TRUE (1 == 1)
#define FALSE (!TRUE)
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct glob_s - global variable
 * @top: pointer to pointer to top of stiack
 * @buf: line buffer storing getline string
 */
typedef struct glob_s
{
	stack_t **top;
	char *buf;
} glob_t;

extern glob_t glob;

/* monty.c */
void stack_int(stack_t **head);
void free_stack(void);

/* process_file.c */
void read_file(const char *filename, stack_t **stack);
void execute_op(stack_t **stack, char *op, unsigned int line_number);
int only_digit(char *num);

/* opcodes_1.c */
void _pall(stack_t **stack, unsigned int line_number);
void _push(stack_t **stack, unsigned int line_number);

#endif
