#include "token.h"


Token::Token(const std::string& type, const std::string& literal):
    type(type),
    literal(literal) {

    }

Token::~Token() {

}
