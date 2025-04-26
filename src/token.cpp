#include "token.h"

std::map<std::string, std::string> Token::KEYWORD_MAP = {
    {"fn", token_type::FUNCTION},
    {"let", token_type::LET},
    {"return", token_type::RETURN},
    {"true", token_type::TRUE},
    {"false", token_type::FALSE},
    {"if", token_type::IF},
    {"else", token_type::ELSE},

};


std::string Token::lookup(const std::string& ident) {
    if(KEYWORD_MAP.find(ident) != KEYWORD_MAP.end())
        return KEYWORD_MAP[ident];

    return token_type::IDENT;
}

Token::Token(const std::string& type, const std::string& literal):
    type(type),
    literal(literal) {

    }

Token::~Token() {

}

