#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "ast.h"


// Top Down Pratt Parser
struct Parser {

    Parser(Lexer* lexer);
    virtual ~Parser();

    Program* parse_programe();
    void next_token();

    Lexer* lexer;

    Token current_token;
    Token peek_token;
};

#endif
