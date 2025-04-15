#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "token.h"

struct Node {
    virtual std::string token_literal() const = 0;
};

struct Statement : Node {
    // statement is something that does not return a value
    virtual std::string token_literal() const = 0 ;
};


struct Expression: Node {
    // expression does return a value
    virtual std::string token_literal() const = 0;
};

struct Identifier : Node {
    // let x

    Identifier(const Token& token, const std::string& value);
    virtual ~Identifier();

    virtual std::string token_literal() const;

    Token token;
    std::string value;

};


struct LetStatement : Statement {
    // let(Token) x(Identifier) = 12(Expression);
    
    LetStatement(const Token& token);
    virtual ~LetStatement();

    virtual std::string token_literal() const;

    Token token;
    Identifier* name;
    Expression* expression;
};


// Main Program that tracks all the statements
struct Program : Node {
    Program();
    virtual ~Program();
    virtual std::string token_literal() const;

    std::vector<Statement*> statements;

};


#endif
