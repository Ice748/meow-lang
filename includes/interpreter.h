#ifndef INTERPRETER_H
#define INTERPRETER_H

typedef enum {
  TOKEN_MODULE,
  TOKEN_DOT,
  TOKEN_FUNCTION,
  TOKEN_LPAREN,
  TOKEN_INT,
  TOKEN_STRING,
  TOKEN_RPAREN,
  TOKEN_EOF,
  TOKEN_UNKNOWN
} TokenType;

typedef struct {
  TokenType type;
  char value[256];
} Token;

int lexer(char str[256], Token *tokens);
char *parser(Token *tokens);
int run(void);

#endif
