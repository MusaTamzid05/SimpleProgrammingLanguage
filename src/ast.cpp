#include "ast.h"


Identifier::Identifier(const Token& token, const std::string& value):
    token(token),
    value(value) {
}

Identifier::~Identifier() {
}


std::string Identifier::token_literal() const {
    return token.literal;
}

std::string Identifier::string() const {
    return value;
}

LetStatement::LetStatement(const Token& token):token(token), value(nullptr) {

}

LetStatement::~LetStatement() {
    delete name;
}


std::string LetStatement::token_literal() const {
    return token.literal;
}


std::string LetStatement::string() const {
    std::string output = "";

    output += token_literal() + " ";
    output += name->string();

    if(value != nullptr)
        output += value->string();



    return output;
}


ReturnStatement::ReturnStatement(const Token& token):
    token(token),
    return_value(nullptr) {}

ReturnStatement::~ReturnStatement() {

}

std::string ReturnStatement::token_literal() const {
    return token.literal;
}

std::string ReturnStatement::string() const {
    std::string output = "";

    output += token_literal() + " ";

    if(return_value != nullptr)
        output += return_value->string();

    return output;
}


Program::Program() {

}

Program::~Program() {

}



std::string Program::token_literal() const {
    if(statements.size())
        return statements[0]->token_literal();

    return "";
}

std::string Program::string() const {
    std::string output = "";

    for(Statement* statement : statements)
        output += statement->string();

    return output;
}

ExpressionStatement::ExpressionStatement(const Token& token):token(token), expression(nullptr) {

}

ExpressionStatement::~ExpressionStatement() {}


std::string ExpressionStatement::token_literal() const {
    return token.literal;
}

std::string ExpressionStatement::string() const {
    if(expression != nullptr)
        return expression->string();

    return "";
}


IntegerLiteral::IntegerLiteral(const Token& token):token(token) {}

IntegerLiteral::~IntegerLiteral() {

}

std::string IntegerLiteral::token_literal() const {
    return token.literal;
}


std::string IntegerLiteral::string() const {
    return token.literal;
}

PrefixTokenExpression::PrefixTokenExpression(const Token& token):
    token(token), 
    operator_(""), 
    right(nullptr) {
}

PrefixTokenExpression::~PrefixTokenExpression() {

}


std::string PrefixTokenExpression::token_literal() const {
    return token.literal;
}


std::string PrefixTokenExpression::string() const {
    std::string output = "";
    output += "(";
    output += operator_;
    output += right->string();
    output += ")";

    return output;
}



InfixTokenExpression::InfixTokenExpression(Expression* left, const Token& token):
    left(left),
    token(token),
    right(nullptr) {
        operator_ = token.literal;
    }


InfixTokenExpression::~InfixTokenExpression() {

}


std::string InfixTokenExpression::token_literal() const {
    return token.literal;
}


std::string InfixTokenExpression::string() const {
    std::string output = "";
    output += "(";
    output += left->string();
    output += " " + operator_ + " ";
    output += right->string();
    output += ")";

    return output;

}










