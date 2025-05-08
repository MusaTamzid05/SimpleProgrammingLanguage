#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "ast.h"
#include "expression_parser.h"
#include <map>


struct Parser {

    enum Precedence {
        LOWEST,
        EQUALS,
        LESS_GREATER
    };

    Parser(Lexer* lexer);
    virtual ~Parser();

    Statement* parse_statement();
    Statement* parse_let_statement();
    Statement* parse_return_statement();


    ExpressionStatement* parse_expression_statement();
    Expression* parse_expression(const Precedence& precedence);

    Program* parse_program();

    bool expect_peek(const std::string& token_type);
    bool peek_token_is(const std::string& token_type) const;
    void peek_error(const std::string& token_type);


    void next_token();

    Lexer* lexer;

    Token current_token;
    Token peek_token;

    std::vector<std::string> error_messages;

    std::map<std::string, PrefixExpressionParser*> prefix_expression_parsers;
};

#endif
