#include "../headers/debug.h"
#include <stdint.h>
#include <stdio.h>

void	disassemble_chunk(t_chunk *chunk, const char *name)
{
	int	offset;

	printf("== %s ==\n", name);
	offset = 0;
	while (offset < chunk->count)
		offset = disassemble_instruction(chunk, offset);
}

static int	simple_instruction(const char *name, int offset)
{
	printf("%s\n", name);
	return (offset + 1);
}

static int	constant_instruction(const char *name, t_chunk *chunk, int offset)
{
	uint8_t	constant;
	constant = chunk->code[offset + 1];
	printf("%-16s %4d '", name, constant);
	print_value(chunk->constants.values[constant]);
	printf("'\n");
	return (offset + 2);
}

int	disassemble_instruction(t_chunk *chunk, int offset)
{
	uint8_t	instruction;	

	printf("%04d ", offset);
	if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) 
		printf("   | ");
	else
		printf("%4d ", chunk->lines[offset]);
	instruction = chunk->code[offset];
	switch (instruction)
	{
		case OP_CONSTANT:
			return constant_instruction("OP_CONSTANT", chunk, offset);
		case OP_ADD:
			return constant_instruction("OP_ADD", chunk, offset);
		case OP_SUBTRACT:
			return constant_instruction("OP_SUBTRACT", chunk, offset);
		case OP_MULTIPLY:
			return constant_instruction("OP_MULTIPLY", chunk, offset);
		case OP_DIVIDE:
			return simple_instruction("OP_DIVIDE", offset);
		case OP_NEGATE:
			return simple_instruction("OP_NEGATE", offset);
		case OP_RETURN:
			return simple_instruction("OP_RETURN", offset);
		default:
			printf("Unknown operation code %d\n", instruction);
			return offset + 1;
	}
}
