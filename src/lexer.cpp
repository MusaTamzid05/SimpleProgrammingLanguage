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
    skip_whitespace();

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
        case ',':
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

            if(is_letter(ch)) {
                token.literal = read_identifier();
                token.type = Token::lookup(token.literal);
                return token;

            } else if(is_digit(ch)) {
                token.type = token_type::INT;
                token.literal = read_number();
                return token;

            } else {
                token = Token(token_type::ILLEGAL, std::string() + ch);
            }

            break;


    }

    read_char();
    return token;

}

bool Lexer::is_letter(char target_ch) const {
    return (target_ch >= 'a' && target_ch <= 'z') || (target_ch >= 'A' && target_ch <= 'Z') || target_ch == '_';
}


std::string Lexer::read_identifier() {
    int original_position = position;

    while(is_letter(ch)) 
        read_char();

    return input.substr(original_position, position - original_position);
}


bool Lexer::is_digit(char target_ch) const {
    return target_ch >= '0' && target_ch <= '9';
}


std::string Lexer::read_number() {
    int original_position = position;

    while(is_digit(ch)) 
        read_char();

    return input.substr(original_position, position - original_position);
}


void Lexer::skip_whitespace() {
    bool running = true;

    while(running) {
        if(ch == '\n' || ch == '\t' || ch == '\r' || ch == ' ')
            read_char();
        else
            running = false;
    }

}
