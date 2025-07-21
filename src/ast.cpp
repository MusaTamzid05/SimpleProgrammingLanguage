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



BooleanExpression::BooleanExpression(const Token& token, bool value):
    token(token), value(value) {

    }

BooleanExpression::~BooleanExpression() {

}




std::string BooleanExpression::token_literal() const {
    return token.literal;
}

std::string BooleanExpression::string() const {
    return token.literal;
}


BlockStatement::BlockStatement(const Token& token):
    token(token) {

}


BlockStatement::~BlockStatement() {

}


std::string BlockStatement::token_literal() const {
    return token.literal;
}


std::string BlockStatement::string() const {
    std::string output = "";

    for(Statement* statement : statements)
        output += statement->string() + " ";

    return output;

}


IfExpression::IfExpression(const Token& token):
    token(token),
    condition(nullptr),
    consequence(nullptr),
    alternative(nullptr) {

    }


IfExpression::~IfExpression() {

}

std::string IfExpression::token_literal() const {
    return token.literal;
}


std::string IfExpression::string() const {
    std::string output = "";
    output += "if ";
    output += condition->string();
    output += " ";

    output += consequence->string();
    output += " ";

    if(alternative != nullptr) {
        output += "else ";
        output += alternative->string();
    }

    return output;

}




FunctionalLiteral::FunctionalLiteral(const Token& token):
    token(token) {

    }


FunctionalLiteral::~FunctionalLiteral() {

}

std::string FunctionalLiteral::token_literal() const {
    return token.literal;
}


std::string FunctionalLiteral::string() const {
    std::string output = "";
    output += token.literal;
    output += "(";

    for(Identifier* identifer : parameters)
        output += identifer->string();

    output += ")";
    output += body->string();
    return output;

}
