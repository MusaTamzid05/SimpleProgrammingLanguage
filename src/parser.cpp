#include "parser.h"

Parser::Parser(Lexer* lexer):lexer(lexer) {
    next_token();
    next_token();
}

Parser::~Parser() {

}

void Parser::next_token() {
    current_token = peek_token;
    peek_token = lexer->next_token();
}


Program* Parser::parse_programe() {
    return nullptr;
}
