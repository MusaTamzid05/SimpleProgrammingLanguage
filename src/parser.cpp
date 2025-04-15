#include "parser.h"

Parser::Parser(Lexer* lexer):lexer(lexer) {
    next_token();
    next_token();
}

Parser::~Parser() {

}

Statement* Parser::parse_statement() {
    if(current_token.type == token_type::LET)
        return parse_let_statement();

    return nullptr;
}

Statement* Parser::parse_let_statement() {
    // let x = 12;
    LetStatement* statement = new LetStatement(current_token);

    if(expect_peek(token_type::IDENT) == false) 
        return nullptr;

    statement->name = new Identifier(current_token, current_token.literal);

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



bool Parser::peek_token_is(const Token& token) const {
    return peek_token.type == token.type;
}

bool Parser::expect_peek(const Token& token) {
    if(peek_token_is(token)) {
        next_token();
        return true;
    }

    peek_error(token);
    return false;
}

void Parser::peek_error(const Token& token)  {
    std::string message = "Expect peek token to be " + token.type + " got " + peek_token.type;
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
