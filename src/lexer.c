#include "../headers/main.h"
#include "../headers/lex.h"
#include <string.h>
#include <stdbool.h>


typedef struct s_lexer
{
	const char	*start;
	const char	*curr;
	int			line;
}	t_lexer;


t_lexer	lexer;

void	init_lexer(const char *src)
{
	lexer.start = src;
	lexer.curr = src;
	lexer.line = 1;
}

static bool	is_alpha(char c)
{
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c== '_');
}

static bool	is_digit(char c)
{
	return c >= '0' && c <= '9';
}

static	bool	is_eof(void)
{
	return (*lexer.curr == '\0');
}

static char	lex_next()
{
	lexer.curr++;
	return (lexer.curr[-1]);
}

static char	peek()
{
	return (*lexer.curr);
}

static char	peek_next()
{
	if (is_eof())
		return ('\0');
	return (lexer.curr[1]);
}

static bool	match(char expected)
{
	if (is_eof())
		return (false);
	if (*lexer.curr != expected)
		return (false);
	lexer.curr++;
	return (true);
}

static t_token	l_tokenize(t_token_type	type)
{
	t_token	token;

	token.type = type;
	token.start = lexer.start;
	token.len = (int)(lexer.curr - lexer.start);
	token.line = lexer.line;

	return (token);
}

static t_token	err_token(const char *msg)
{
	t_token	token;

	token.type = TOKEN_ERROR;
	token.start = msg;
	token.len = (int)strlen(msg);
	token.line = lexer.line;

	return (token);
}

static void	skip_whitespace()
{
	while (true)
	{
		char c = peek();
		switch(c)
		{
			case 32:
			case '\r':
			case '\t':
				lex_next();
				break ;
			case '\n':
				lexer.line++;
				lex_next();
				break;
			case '/':
				if (peek_next() == '/')
					while (peek() != '\n' && !is_eof())
						lex_next();
				else
					return ;
				break;
			default:
				return ;
		}
	}
}

static t_token_type	check_keyword(int start, int len,
		const char	*rem, t_token_type type)
{
	if (lexer.curr - lexer.start == start + len &&
			memcmp(lexer.start + start, rem, len))
		return (type);

	return TOKEN_IDENTIFIER;
}

static t_token_type	ident_type(void)
{
	switch (lexer.start[0])
	{
		case 'a':
			return check_keyword(1, 2, "nd", TOKEN_AND);
		case 'c':
			return check_keyword(1, 4, "lass", TOKEN_CLASS);
		case 'e':
			return check_keyword(1, 3, "lse", TOKEN_ELSE);
		case 'f':
			if (lexer.curr - lexer.start > 1)
			{
				switch (lexer.start[1])
				{
					case 'a':
						return check_keyword(2, 3, "lse", TOKEN_FALSE);
					case 'o':
						return check_keyword(2, 1, "r", TOKEN_FOR);
					case 'u':
						return check_keyword(2, 1, "n", TOKEN_FUN);
				}
			}
			break;
		case 'i':
			return check_keyword(1, 1, "f", TOKEN_IF);
		case 'n':
			return check_keyword(1, 2, "il", TOKEN_NIL);
		case 'o':
			return check_keyword(1, 1, "r", TOKEN_OR);
		case 'p':
			return check_keyword(1, 4, "rint", TOKEN_PRINT);
		case 'r':
			return check_keyword(1, 5, "eturn", TOKEN_RETURN);
		case 's':
			return check_keyword(1, 4, "uper", TOKEN_SUPER);
		case 't':
			if (lexer.curr - lexer.start > 1)
			{
				switch (lexer.start[1])
				{
					case 'h':
						return check_keyword(2, 2, "is", TOKEN_THIS);
					case 'r':
						return check_keyword(2, 2, "ue", TOKEN_TRUE);
				}
			}
			break;
		case 'v':
			return check_keyword(1, 2, "ar", TOKEN_VAR);
		case 'w':
			return check_keyword(1, 4, "hile", TOKEN_WHILE);
	}
	return (TOKEN_IDENTIFIER);
}

static t_token	handle_identifier()
{
	while (is_alpha(peek()) || is_digit(peek()))
			lex_next();
	return (l_tokenize(ident_type()));
}

static t_token	handle_number()
{
	while (is_digit(peek()))
		lex_next();

	if (peek() == '.' && is_digit(peek_next()))
	{
		lex_next();
		while (is_digit(peek()))
			lex_next();
	}

	return (l_tokenize(TOKEN_NUMBER));
}

static t_token	handle_string()
{
	while (peek() != '"' && !is_eof())
	{
		if (peek() == '\n')
			lexer.line++;
		lex_next();
	}

	if (is_eof())
		return (err_token("Unterminated string :(."));

	lex_next();
	return (l_tokenize(TOKEN_STRING));
}

t_token	lex_token(void)
{
	char	c;
	skip_whitespace();
	lexer.start = lexer.curr;
	if (is_eof())
		return (l_tokenize(TOKEN_EOF));
	c = lex_next();
	if (is_alpha(c))
		return (handle_identifier());
	if (is_digit(c))
		return (handle_number());

	switch (c)
	{
		case '(': return l_tokenize(TOKEN_LEFT_PAREN);
		case ')': return l_tokenize(TOKEN_RIGHT_PAREN);
		case '{': return l_tokenize(TOKEN_LEFT_BRACE);
		case '}': return l_tokenize(TOKEN_RIGHT_BRACE);
		case ';': return l_tokenize(TOKEN_SEMICOLON);
		case ',': return l_tokenize(TOKEN_COMMA);
		case '.': return l_tokenize(TOKEN_DOT);
		case '-': return l_tokenize(TOKEN_MINUS);
		case '+': return l_tokenize(TOKEN_PLUS);
		case '/': return l_tokenize(TOKEN_SLASH);
		case '*': return l_tokenize(TOKEN_STAR);
		case '!': 
				  return l_tokenize(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
		case '=':
				  return l_tokenize(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
		case '<':
				  return l_tokenize(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
		case '>':
				  return l_tokenize(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
		case '"': return handle_string();
	}

	return (err_token("Unexpected character."));
}
