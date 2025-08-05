#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "token.h"

struct Node {
    virtual std::string token_literal() const = 0;
    virtual std::string string() const = 0;
};

struct Statement : Node {
    // statement is something that does not return a value
    virtual std::string token_literal() const = 0 ;
    virtual std::string string() const = 0;
};


struct Expression: Node {
    // expression does return a value
    virtual std::string token_literal() const = 0;
    virtual std::string string() const = 0;
};

struct Identifier : Expression {
    // let x

    Identifier(const Token& token, const std::string& value);
    virtual ~Identifier();

    virtual std::string token_literal() const;
    virtual std::string string() const;

    Token token;
    std::string value;

};


struct LetStatement : Statement {
    // let(Token) x(Identifier) = 12(Expression);
    
    LetStatement(const Token& token);
    virtual ~LetStatement();

    virtual std::string token_literal() const;
    virtual std::string string() const;

    Token token;
    Identifier* name;
    Expression* value;
};

struct ReturnStatement : Statement {
    // return (token) x (expression)

    ReturnStatement(const Token& token);
    virtual ~ReturnStatement();

    virtual std::string token_literal() const;
    virtual std::string string() const;

    Token token;
    Expression* return_value;

};


// Main Program that tracks all the statements
struct Program : Node {
    Program();
    virtual ~Program();
    virtual std::string token_literal() const;
    std::string string() const;


    std::vector<Statement*> statements;

};

struct ExpressionStatement : Statement {
    ExpressionStatement(const Token& token);
    virtual ~ExpressionStatement();


    virtual std::string token_literal() const;
    std::string string() const;

    Token token;
    Expression* expression;

};

struct IntegerLiteral : Expression {
    IntegerLiteral(const Token& token);
    virtual ~IntegerLiteral();

    std::string token_literal() const;
    std::string string() const;

    Token token;
    int value;

};

struct PrefixTokenExpression : Expression {
    // !5, -3
    PrefixTokenExpression(const Token& token);
    virtual ~PrefixTokenExpression();

    std::string token_literal() const;
    std::string string() const;

    Token token;
    std::string operator_;
    Expression* right;
};


struct InfixTokenExpression : Expression {
    // 5 + 3
    InfixTokenExpression(Expression* left, const Token& token);
    virtual ~InfixTokenExpression();

    std::string token_literal() const;
    std::string string() const;

    Token token;

    Expression* left;
    std::string operator_;
    Expression* right;
};

struct BooleanExpression : Expression {
    BooleanExpression(const Token& token, bool value);
    virtual ~BooleanExpression();

    std::string token_literal() const;
    std::string string() const;

    Token token;
    bool value;
};

struct BlockStatement : Expression {
    // { this is a block_statement }
    BlockStatement(const Token& token);
    virtual ~BlockStatement();

    std::string token_literal() const;
    std::string string() const;

    Token token;
    std::vector<Statement*> statements;

};


struct IfExpression : Expression  {
    // If (condition) { consequence } else { alternative }

    IfExpression(const Token& token);
    ~IfExpression();

    std::string token_literal() const;
    std::string string() const;


    Token token;
    Expression* condition;
    BlockStatement* consequence;
    BlockStatement* alternative;


};


struct FunctionalLiteral : Expression {
    // fn(x,y) { x + y;}
    FunctionalLiteral(const Token& token);
    virtual ~FunctionalLiteral();


    std::string token_literal() const;
    std::string string() const;

    Token token; // fn
    std::vector<Identifier*> parameters; // (x, y)
    BlockStatement* body; // { x + y; }

};



struct CallExpression : Expression {
    // test(x, y + z);
    
    CallExpression(const Token& token, Expression* function);
    virtual ~CallExpression();

    std::string token_literal() const;
    std::string string() const;

    Token token; // (
    Expression* function;
    std::vector<Expression*> arguments; 


};
















#endif
