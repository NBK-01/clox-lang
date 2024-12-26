#include "../headers/main.h"
#include <stdint.h>
#include <stdio.h>
#include "../headers/vm.h"
#include "../headers/debug.h"

t_vm	vm;

static void	reset_stack(void)
{
	vm.stack_top = vm.stack;
}

void	init_vm()
{
	reset_stack();
	/*COME BACK TO LATER */
}

void	free_vm()
{
	/*COME BACK TO LATER */
}

void	push(Value val)
{
	*vm.stack_top = val;
	vm.stack_top++;
}

Value	pop(void)
{
	vm.stack_top--;
	return (*vm.stack_top);
}

static t_interpreter_res	run(void)
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
	do { \
		double b = pop(); \
		double a = pop(); \
		push(a op b); \
	} while (false)

	for(;;)
	{
#ifdef DEBUG_TRACE_EXECUTION
		printf("               ");
		for (Value *slot = vm.stack; slot < vm.stack_top; slot++)
		{	
			printf("[ ");
			print_value(*slot);
			printf("  ]");
		}
		printf("\n");
		disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
		uint8_t	instruction;
		switch (instruction = READ_BYTE())
		{
			case OP_CONSTANT:
			{
				Value constant = READ_CONSTANT();
				push(constant);
				break ;
			}
			case OP_ADD: BINARY_OP(+); break;
			case OP_SUBTRACT: BINARY_OP(-); break;
			case OP_MULTIPLY: BINARY_OP(*); break;
			case OP_DIVIDE: BINARY_OP(/); break;
			case OP_NEGATE: push(-pop()); break;
			case OP_RETURN:
			{
				print_value(pop());
				printf("\n");
				return INTERPRET_OK;
			}
		}
	}

#undef READ_BYTE
#undef READE_CONSTANT
#undef BINARY_OP
}

t_interpreter_res	interpret(const char *src)
{
	t_chunk	chunk;
	init_chunk(&chunk);
	if (!compile(src, &chunk))
	{
		free_chunk(&chunk);
		return (INTERPRET_COMPILER_ERROR);
	}
	vm.chunk = &chunk;
	vm.ip = vm.chunk->code;

	t_interpreter_res result = run();
	free_chunk(&chunk);

	return (result);
}


