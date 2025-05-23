#include "expression_parser.h"
#include <string>

IdentifierExpressionParser::IdentifierExpressionParser() {

}


IdentifierExpressionParser::~IdentifierExpressionParser() {

}

Expression* IdentifierExpressionParser::parse(const Token& token) {
    Identifier* identifier = new Identifier(token, token.literal);
    return identifier;

}


IntegerExpressionParser::IntegerExpressionParser() {

}

IntegerExpressionParser::~IntegerExpressionParser() {

}


Expression* IntegerExpressionParser::parse(const Token& token) {
    IntegerLiteral* literal = new IntegerLiteral(token);
    int value = stoi(token.literal);
    literal->value = value;
    return literal;

}
