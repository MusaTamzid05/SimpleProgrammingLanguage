#include "parser.h"

Parser::Parser(Lexer* lexer):lexer(lexer) {
    next_token();
    next_token();

    prefix_expression_parsers[token_type::IDENT] = new IdentifierExpressionParser();
    prefix_expression_parsers[token_type::INT] = new IntegerExpressionParser();
}

Parser::~Parser() {

}

Statement* Parser::parse_statement() {
    if(current_token.type == token_type::LET)
        return parse_let_statement();

    else if(current_token.type == token_type::RETURN)
        return parse_return_statement();

    return parse_expression_statement();
}

Statement* Parser::parse_let_statement() {
    // let x = 12;
    LetStatement* statement = new LetStatement(current_token);

    if(expect_peek(token_type::IDENT) == false) 
        return nullptr;

    statement->name = new Identifier(current_token, current_token.literal);

    if(expect_peek(token_type::ASSIGN) == false) 
        return nullptr;

    // move till ';' is found

    bool end_found = false;

    while(end_found == false) {
        if(current_token.type == token_type::SEMICOLON) {
            end_found = true;
            continue;
        }

        if(current_token.type == token_type::EOF_TYPE) {
            error_messages.push_back("';' missing in the end.");
            return nullptr;
        }

        next_token();

    }
    

    return statement;
}

Statement* Parser::parse_return_statement() {
    // return 123;
    ReturnStatement* statement = new ReturnStatement(current_token);
    next_token();


    // move till ';' is found

    bool end_found = false;

    while(end_found == false) {
        if(current_token.type == token_type::SEMICOLON) {
            end_found = true;
            continue;
        }

        if(current_token.type == token_type::EOF_TYPE) {
            error_messages.push_back("';' missing in the end.");
            return nullptr;
        }

        next_token();

    }
    

    return statement;
    
}




bool Parser::peek_token_is(const std::string& token_type) const {
    return peek_token.type == token_type;
}

bool Parser::expect_peek(const std::string& token_type) {
    if(peek_token_is(token_type)) {
        next_token();
        return true;
    }

    peek_error(token_type);
    return false;
}

void Parser::peek_error(const std::string& token_type)  {
    std::string message = "Expect peek token to be " + token_type + " got " + peek_token.type;
    error_messages.push_back(message);
}

void Parser::next_token() {
    current_token = peek_token;
    peek_token = lexer->next_token();
}


Program* Parser::parse_program() {
    Program* program = new Program();

    while(current_token.type != token_type::EOF_TYPE) {
        Statement* statement = parse_statement();

        if(statement != nullptr)
            program->statements.push_back(statement);

        next_token();
    }

    return program;
}


ExpressionStatement* Parser::parse_expression_statement() {
    ExpressionStatement* statement = new ExpressionStatement(current_token);
    statement->expression = parse_expression(Precedence::LOWEST);

    if(peek_token_is(token_type::SEMICOLON)) 
        next_token();

    
    return statement;
}


Expression* Parser::parse_expression(const Precedence& precedence) {
    if(prefix_expression_parsers.find(current_token.type) == prefix_expression_parsers.end())
        return nullptr;

    PrefixExpressionParser* prefix_express_parser =  prefix_expression_parsers[current_token.type];
    Expression* left_expression = prefix_express_parser->parse(current_token);

   return left_expression ;

}


