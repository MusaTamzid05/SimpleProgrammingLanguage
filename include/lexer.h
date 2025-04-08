#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"

struct Lexer {
    Lexer(const std::string& input);
    virtual ~Lexer();

    void read_char();
    Token next_token();

    std::string input;
    char ch;
    int position; // index of last read char
    int read_position; // index of next char to be read


};

#endif
