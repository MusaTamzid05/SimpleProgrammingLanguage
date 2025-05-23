#include "expression_parser.h"
#include <string>
#include "parser.h"

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

PrefixTokenExpressionParser::PrefixTokenExpressionParser(Parser* parser):parser(parser) {
}

PrefixTokenExpressionParser::~PrefixTokenExpressionParser() {
}


Expression* PrefixTokenExpressionParser::parse(const Token& token) {
    PrefixTokenExpression* prefix_expression = new PrefixTokenExpression(token);
    prefix_expression->operator_ = token.literal;

    parser->next_token();

    prefix_expression->right = parser->parse_expression(Parser::Precedence::PREFIX);

    return prefix_expression;

}
