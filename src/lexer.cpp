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
            if(peek_char() == '=') {
                char current_char = ch;
                read_char();
                std::string eq_literal = (std::string() + current_char) + (std::string() + current_char);
                token = Token(token_type::EQ, eq_literal);
            } else {
                token = Token(token_type::ASSIGN, "=");
            }
            break;
        case ';':
            token = Token(token_type::SEMICOLON, ";");
            break;
        case '+':
            token = Token(token_type::PLUS, "+");
            break;
        case '-':
            token = Token(token_type::MINUS, "-");
            break;
        case ',':
            token = Token(token_type::COMMA, ",");
            break;
        case '*':
            token = Token(token_type::ASTERISK, "*");
            break;
        case '/':
            token = Token(token_type::SLASH, "/");
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
        case '>':
            token = Token(token_type::GT, ">");
            break;
        case '<':
            token = Token(token_type::LT, "<");
            break;
        case '!':
            if(peek_char() == '=') {
                char current_char = ch;
                read_char();
                std::string eq_literal = (std::string() + current_char) + (std::string() + ch);
                token = Token(token_type::NOT_EQ, eq_literal);
            } else {
                token = Token(token_type::BANG, "!");
            }

            break;
        case 0:
            token = Token(token_type::EOF_TYPE, "");
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


char Lexer::peek_char() const {
    if(read_position >= input.size())
        return 0;

    return input[read_position];
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
