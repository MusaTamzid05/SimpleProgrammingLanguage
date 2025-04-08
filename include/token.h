#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

namespace token_type {
    const std::string ILLEGAL = "ILLEGAL";
    const std::string EOF_TYPE = "EOF";

    // Identifiers + literals
    const std::string IDENT = "IDENT"; // add, foobar, x, y, ...
    const std::string INT = "INT";

    const std::string ASSIGN = "=";
    const std::string PLUS = "+";

    // Delimiters
    const std::string COMMA = ",";
    const std::string SEMICOLON = ";";
    const std::string LPAREN = "(";
    const std::string RPAREN = ")";
    const std::string LBRACE = "{";
    const std::string RBRACE = "}";

    // Keywords
    const std::string FUNCTION = "FUNCTION";
    const std::string LET = "LET";

}

struct Token {
    Token(const std::string& type="", const std::string& literal="");
    virtual ~Token();

    std::string type;
    std::string literal;

    static std::map<std::string, std::string> KEYWORD_MAP;
    static std::string lookup(const std::string& ident);
};

#endif
