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
    const std::string MINUS = "-";
    const std::string ASTERISK = "*";
    const std::string SLASH = "/";

    const std::string LT = "<";
    const std::string GT = ">";
    const std::string BANG = "!";
    const std::string EQ = "==";
    const std::string NOT_EQ = "!=";

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
    const std::string RETURN = "RETURN";
    const std::string TRUE = "TRUE";
    const std::string FALSE = "FALSE";
    const std::string IF = "IF";
    const std::string ELSE = "ELSE";

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
