#include "expression_parser.h"

IdentifierExpressionParser::IdentifierExpressionParser() {

}


IdentifierExpressionParser::~IdentifierExpressionParser() {

}

Expression* IdentifierExpressionParser::parse(const Token& token) const {
    Identifier* identifier = new Identifier(token, token.literal);
    return identifier;

}
