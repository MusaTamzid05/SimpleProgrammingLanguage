#include "lexer.h"

Lexer::Lexer(const std::string& input):
    input(input),
    position(0),
    read_position(0),
    ch(0) {
        read_char();

}

Lexer::~Lexer() {

}

void Lexer::read_char() {
    // update the read postion
    // according to the current char
    
    if(read_position >= input.size())  {
        ch = 0;
    } else 
         ch = input[read_position];

    position = read_position;
    read_position += 1;

}

Token Lexer::next_token() {
    Token token;

    switch(ch) {
        case '=':
            token = Token(TokenType::ASSIGN, "=");
            break;
        case ';':
            token = Token(TokenType::SEMICOLON, ";");
            break;
        case '+':
            token = Token(TokenType::PLUS, "+");
            break;
        case '-':
            token = Token(TokenType::COMMA, ",");
            break;
        case '(':
            token = Token(TokenType::LPAREN, "(");
            break;
        case ')':
            token = Token(TokenType::RPAREN, ")");
            break;
        case '{':
            token = Token(TokenType::LBRACE, "{");
            break;
        case '}':
            token = Token(TokenType::RBRACE, "}");
            break;
        case 0:
            token = Token(TokenType::EOF_TYPE, "");
            break;

    }

    return token;

}
