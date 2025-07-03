#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "ast.h"

struct Parser;


struct PrefixExpressionParser {
    virtual Expression* parse(const Token& token) = 0;
};

struct IdentifierExpressionParser : PrefixExpressionParser {
    IdentifierExpressionParser();
    virtual ~IdentifierExpressionParser();

    Expression* parse(const Token& token);
};


struct IntegerExpressionParser : PrefixExpressionParser {
    IntegerExpressionParser();
    virtual ~IntegerExpressionParser();

    Expression* parse(const Token& token);

};


struct PrefixTokenExpressionParser : PrefixExpressionParser {
    PrefixTokenExpressionParser(Parser* parser);
    virtual ~PrefixTokenExpressionParser();

    Expression* parse(const Token& token);
    Parser* parser;

};



struct InfixTokenExpressionParser {
    InfixTokenExpressionParser(Parser* parser);
    virtual ~InfixTokenExpressionParser();

    Expression* parse(Expression* left);
    Parser* parser;

};


struct BooleanExpressionParser: PrefixExpressionParser {
    BooleanExpressionParser(Parser* parser);
    virtual ~BooleanExpressionParser();

    Expression* parse(const Token& token);
    Parser* parser;

};




#endif
