#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"

struct Lexer {
    Lexer(const std::string& input);
    virtual ~Lexer();

    void read_char();
    Token next_token();

    void skip_whitespace();
    bool is_letter(char target_ch) const;
    std::string read_identifier();


    bool is_digit(char target_ch) const;
    std::string read_number();

    std::string input;
    char ch;
    int position; // index of last read char
    int read_position; // index of next char to be read


};

#endif
