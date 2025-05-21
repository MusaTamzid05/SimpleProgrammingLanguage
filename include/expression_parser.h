#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "ast.h"


struct PrefixExpressionParser {
    virtual Expression* parse(const Token& token) const  = 0;
};

struct IdentifierExpressionParser : PrefixExpressionParser {
    IdentifierExpressionParser();
    virtual ~IdentifierExpressionParser();

    Expression* parse(const Token& token) const;
};


struct IntegerExpressionParser : PrefixExpressionParser {
    IntegerExpressionParser();
    virtual ~IntegerExpressionParser();

    Expression* parse(const Token& token) const;

};



#endif
