#include "../headers/main.h"
#include "../headers/chunk.h"
#include "../headers/mem.h"

void	init_chunk(t_chunk *chunk)
{
	chunk->capacity = 0;
	chunk->count = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	init_value_array(&chunk->constants);
}

void	write_chunk(t_chunk *chunk, uint8_t byte, int line)
{
	int	old_cap;

	if (chunk->capacity < chunk->count + 1)
	{
		old_cap = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(old_cap);
		chunk->code = GROW_ARR(uint8_t, chunk->code, old_cap,
				chunk->capacity);
		chunk->lines = GROW_ARR(int, chunk->lines, old_cap, chunk->capacity);
	}
	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

void	free_chunk(t_chunk *chunk)
{
	FREE_ARR(uint8_t, chunk->code, chunk->capacity);
	FREE_ARR(int, chunk->lines, chunk->capacity);
	free_value_array(&chunk->constants);
	init_chunk(chunk);
}

int		add_constant(t_chunk *chunk, Value val)
{
	write_value_array(&chunk->constants, val);
	return (chunk->constants.count - 1);
}
