#include "../headers/main.h"
#include "../headers/lex.h"
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../headers/chunk.h"

typedef struct s_parser {
	t_token	curr;
	t_token	prev;
	bool	err;
	bool	panic;
}	t_parser;

t_parser	parser;
t_chunk		*compiler_chunk;

static t_chunk	*curr_chunk(void)
{
	return compiler_chunk;
}

static void	err_loc(t_token *token, const char *msg)
{
	if (parser.panic)
		return ;
	parser.panic = true;
	fprintf(stderr, "[line %d] Err", token->line);

	if (token->type == TOKEN_EOF)
		fprintf(stderr, " at EOF");
	else if (token->type == TOKEN_ERROR)
	{

	}
	else {
		fprintf(stderr, " at '%.*s'", token->len, token->start);
	}

	fprintf(stderr, " at '%.*s'", token->len, token->start);
	parser.err = true;
}

static void	error(const char *msg)
{
	err_loc(&parser.prev, msg);
}

static void	err_at_curr(const char	*msg)
{
	err_loc(&parser.curr, msg);
}

static void	advance(void)
{
	parser.prev = parser.curr;

	while (true)
	{
		parser.curr = lex_token();
		if (parser.curr.type != TOKEN_ERROR)
			break ;

		err_at_curr(parser.curr.start);
	}
}

static void	consume(t_token_type type, const char *msg)
{
	if (parser.curr.type == type)
	{
		advance();
		return ;
	}
	err_at_curr(msg);
}

static void	emit_byte(uint8_t byte)
{
	write_chunk(curr_chunk(), byte, parser.prev.line);
}

static void	emit_bytes(uint8_t byte1, uint8_t byte2)
{
	emit_byte(byte1);
	emit_byte(byte2);
}

static void	emit_return(void)
{
	emit_byte(OP_RETURN);
}

static uint8_t	make_const(Value val)
{
	int	constant = add_constant(curr_chunk(), val);
	if (constant > UINT8_MAX)
	{
		error("Too many constants in chunk");
		return (EXIT_FAILURE);
	}

	return ((uint8_t)constant);
}

static void	emit_const(Value val)
{
	emit_bytes(OP_CONSTANT, make_const(val));
}

static void end_compiler(void)
{
	emit_return();
}

static void	grouping(void)
{
	expr();
	consume(TOKEN_RIGHT_PAREN, "Expect ')' after expr");
}

static void	number(void)
{
	double	val = strtod(parser.prev.start, NULL);
	emit_const(val);
}

static void	unary(void)
{
	t_token_type	op_type;

	op_type = parser.prev.type;
	expr();
	switch (op_type) {
		case TOKEN_MINUS: emit_byte(OP_NEGATE); break;
		default: return;
	}
}

static void	expr(void)
{

}

bool	compile(const char *src, t_chunk *chunk)
{
	init_lexer(src);

	compiler_chunk = chunk;
	parser.err = false;
	parser.panic = false;

	advance();
	expr();
	consume(TOKEN_EOF, "Expect EOE");
	end_compiler();
	return !parser.err;
}
