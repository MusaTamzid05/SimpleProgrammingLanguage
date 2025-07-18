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


GroupExpressionParser::GroupExpressionParser(Parser* parser):parser(parser) {

}

GroupExpressionParser::~GroupExpressionParser() {

}


Expression* GroupExpressionParser::parse(const Token& token) {
    // (1 + 2) 
    
    parser->next_token();
    Expression* expression = parser->parse_expression(Parser::Precedence::LOWEST);

    if(!parser->expect_peek(token_type::RPAREN))
        return nullptr;
    return expression;

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


InfixTokenExpressionParser::InfixTokenExpressionParser(Parser* parser):
    parser(parser) {

    }


InfixTokenExpressionParser::~InfixTokenExpressionParser() {

}

Expression* InfixTokenExpressionParser::parse(Expression* left) {
    // 1 + 2, current token will be '+'   when it is called
    InfixTokenExpression* expression = new InfixTokenExpression(left, parser->current_token);
    Parser::Precedence precedence = parser->current_precedence();
    parser->next_token();

    expression->right = parser->parse_expression(precedence);
    return expression;
}


BooleanExpressionParser::BooleanExpressionParser(Parser* parser):
    parser(parser) {

    }


BooleanExpressionParser::~BooleanExpressionParser() {}



Expression* BooleanExpressionParser::parse(const Token& token) {
    return new BooleanExpression(token, parser->current_token_is(token_type::TRUE));
}



IfExpressionParser::IfExpressionParser(Parser* parser):
    parser(parser) {

    }

IfExpressionParser::~IfExpressionParser() {

}
    

Expression* IfExpressionParser::parse(const Token& token) {
    IfExpression* if_expression = new IfExpression(token);

    // If (condition) { consequence } else { alternative }

    if(!parser->expect_peek(token_type::LPAREN))
        return nullptr;

    parser->next_token();
    if_expression->condition = parser->parse_expression(Parser::Precedence::LOWEST);

    if(!parser->expect_peek(token_type::RPAREN))
        return nullptr;

    if(!parser->expect_peek(token_type::LBRACE))
        return nullptr;

    BlockStatementParser* block_parser = new BlockStatementParser(parser);
    if_expression->consequence = block_parser->parse(parser->current_token);


    if(parser->peek_token_is(token_type::ELSE)) {
        parser->next_token();

        if(!parser->expect_peek(token_type::LBRACE))
            return nullptr;

        if_expression->alternative = block_parser->parse(parser->current_token);

    }

    return if_expression;

}

BlockStatementParser::BlockStatementParser(Parser* parser): parser(parser) {

}

BlockStatementParser::~BlockStatementParser() {

}


BlockStatement* BlockStatementParser::parse(const Token& token) {
    BlockStatement* block = new BlockStatement(token);
    parser->next_token();

    while(!parser->current_token_is(token_type::RBRACE)) {
        Statement* statement = parser->parse_statement();

        if(statement != nullptr)
            block->statements.push_back(statement);

        parser->next_token();

    }

    return block;
}







