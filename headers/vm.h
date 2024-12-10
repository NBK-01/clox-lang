#ifndef VM_H
#define VM_H

#include "chunk.h"
#include <stdint.h>
#include "value.h"

#define STACK_MAX 256

typedef struct s_vm
{
	t_chunk	*chunk;
	uint8_t	*ip;
	Value	stack[STACK_MAX];
	Value	*stack_top;
}	t_vm;

typedef enum e_interpreter_res
{
	INTERPRET_OK,
	INTERPRET_COMPILER_ERROR,
	INTERPRET_RUNTIME_ERROR
}	t_interpreter_res;


void				init_vm(void);
void				free_vm(void);
t_interpreter_res	interpret(const char *src);
void				push(Value val);
Value				pop(void);

#endif
