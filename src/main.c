#include "../headers/vm.h"
#include <stdio.h>


static void	repl()
{
	char	line[1024];

	while (true)
	{
		printf(">>  ");

		if (!fgets(line, sizeof(line), stdin))
		{
			printf("\n");
			break ; 
		}
		interpret(line);
	}
}

static char	*read_file(const char *path)
{
	FILE	*file;
	size_t	file_size;

	file = fopen(path, "rb");
	if (!file)
	{
		fprintf(stderr, "Could not open file \"%s \". \n", path);
		exit(74);
	}
	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	char	*buff = (char *)malloc(file_size + 1);
	if (!buff)
	{
		fprintf(stderr, "Failed to allocate mem");
		exit(74);
	}
	size_t bytes_read = fread(buff, sizeof(char), file_size, file);
	if (bytes_read < file_size)
	{
		fprintf(stderr, "Could not read file");
		exit(74);
	}
	buff[bytes_read] = '\0';

	fclose(file);
	return (buff);
}


static void	run_file(const char *path)
{
	char	*src;
	t_interpreter_res	res;

	src = read_file(path);
	res = interpret(src);
	free(src);

	if (res == INTERPRET_COMPILER_ERROR) exit(65);
	if (res == INTERPRET_RUNTIME_ERROR) exit(70);
}

int	main(int ac, char **av)
{
	init_vm();

	if (ac == 1)
		repl();
	else if (ac == 2)
		run_file(av[1]);
	else {
		fprintf(stderr, "Usage: clox [path]\n");
		exit(64);
	}
	free_vm();
}
