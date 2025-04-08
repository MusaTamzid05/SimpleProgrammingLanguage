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
            token = Token(token_type::ASSIGN, "=");
            break;
        case ';':
            token = Token(token_type::SEMICOLON, ";");
            break;
        case '+':
            token = Token(token_type::PLUS, "+");
            break;
        case '-':
            token = Token(token_type::COMMA, ",");
            break;
        case '(':
            token = Token(token_type::LPAREN, "(");
            break;
        case ')':
            token = Token(token_type::RPAREN, ")");
            break;
        case '{':
            token = Token(token_type::LBRACE, "{");
            break;
        case '}':
            token = Token(token_type::RBRACE, "}");
            break;
        case 0:
            token = Token(token_type::EOF_TYPE, std::string() + ch);
            break;
        default:
            token = Token(token_type::ILLEGAL, std::string() + ch);
            break;


    }

    read_char();
    return token;

}
