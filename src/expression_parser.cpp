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

FunctionalLiteralParser::FunctionalLiteralParser(Parser* parser):parser(parser) {}
FunctionalLiteralParser::~FunctionalLiteralParser() {}


FunctionalLiteralParser::ParseParameterResponse  FunctionalLiteralParser::parse_parameters() const {
    // (x, y)
    ParseParameterResponse parse_parameter_response;

    // handle when there is no paramaters => ()
    if(parser->peek_token_is(token_type::RPAREN))  {
        parse_parameter_response.success = true;
        parser->next_token();
        return parse_parameter_response;
    }

    parser->next_token(); // x
    Identifier* identifier = new Identifier(parser->current_token, parser->current_token.literal);
    parse_parameter_response.identifiers.push_back(identifier);

    // ,y)
    while(parser->peek_token_is(token_type::COMMA)) {
        parser->next_token();
        parser->next_token();

        Identifier* identifier = new Identifier(parser->current_token, parser->current_token.literal);
        parse_parameter_response.identifiers.push_back(identifier);

    }

    // y)
    if(parser->expect_peek(token_type::RPAREN) == false)  {
        parse_parameter_response.success = false;
        return parse_parameter_response;

    }

    parse_parameter_response.success = true;
    return parse_parameter_response;
}

Expression* FunctionalLiteralParser::parse(const Token& token) {
    // fn(x, y) { x + y; }
    FunctionalLiteral* func_literal = new FunctionalLiteral(token); // fn

    if(parser->expect_peek(token_type::LPAREN) == false) 
        return nullptr;

    ParseParameterResponse parameter_parse_response = parse_parameters();

    if(parameter_parse_response.success == false)
        return nullptr;

    func_literal->parameters = parameter_parse_response.identifiers; // (x, y) {x + y;}


    if(parser->expect_peek(token_type::LBRACE) == false)  // { x + y; }
        return nullptr;
    
    BlockStatementParser* block_parser = new BlockStatementParser(parser);
    func_literal->body = block_parser->parse(parser->current_token);

    return func_literal;
}


CallExpressionParser::CallExpressionParser(Parser* parser):InfixTokenExpressionParser(parser) {

}



CallExpressionParser::~CallExpressionParser() {}


Expression* CallExpressionParser::parse(Expression* left) {
    CallExpression* call_expression = new CallExpression(parser->current_token, left);
    ParseArgumentResult argument_result = parse_arguments();

    if(argument_result.success == false)
        return nullptr;

    call_expression->arguments = argument_result.arguments;

    return call_expression;
}

CallExpressionParser::ParseArgumentResult CallExpressionParser::parse_arguments() {
    // (x, y +z, z + y);
    ParseArgumentResult result;
    // (
    
    if(parser->peek_token_is(token_type::RPAREN)) {
        parser->next_token();
        result.success = true;
        return result;
    }

    parser->next_token(); // x,y + z, z + y);
    result.arguments.push_back(parser->parse_expression(Parser::Precedence::LOWEST));

    while(parser->peek_token_is(token_type::COMMA)) { // ,y + z, z + y)
        parser->next_token(); //  y + z, z + y)
        parser->next_token(); 
        result.arguments.push_back(parser->parse_expression(Parser::Precedence::LOWEST));  //   z + y)
    }

    // );
    
    if(parser->expect_peek(token_type::RPAREN) == false) {
        result.success = false;
        return result;
    }

    result.success = true;
    return result;
}



