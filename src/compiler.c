#include "../headers/main.h"
#include "../headers/lex.h"
#include <stdio.h>


void	compiler(const char *src)
{
	init_lexer(src);
	int	line = -1;
	while (true)
	{
		t_token	token = lex_token();

		if (token.line != line)
		{
			printf("%4d", token.line);
			line = token.line;
		}
		else
			printf("    |  ");

		printf("%2d '%.*s'\n", token.type, token.len, token.start);

		if (token.type == TOKEN_EOF)
			break ;
	}
}


