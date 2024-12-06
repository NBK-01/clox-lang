#include "../headers/main.h"
#include "../headers/chunk.h"
#include "../headers/debug.h"
#include "../headers/vm.h"

int main(int ac, char *av[])
{
	init_vm();
	t_chunk	chunk;
	int		constant;

	init_chunk(&chunk);
	constant = add_constant(&chunk, 5.2);
	write_chunk(&chunk, OP_CONSTANT, 123);
	write_chunk(&chunk, constant, 123);
  constant = add_constant(&chunk, 3.4);
  write_chunk(&chunk, OP_CONSTANT, 123);
  write_chunk(&chunk, constant, 123);

  write_chunk(&chunk, OP_ADD, 123);

  constant = add_constant(&chunk, 5.6);
  write_chunk(&chunk, OP_CONSTANT, 123);
  write_chunk(&chunk, constant, 123);

  write_chunk(&chunk, OP_DIVIDE, 123);
	write_chunk(&chunk, OP_NEGATE, 123);
	write_chunk(&chunk, OP_RETURN, 123);
	disassemble_chunk(&chunk, "test chunk");
	interpret(&chunk);
	free_vm();
	free_chunk(&chunk);

	return (0);
}
