#include "ast.h"


Identifier::Identifier(const Token& token, const std::string& value):
    token(token),
    value(value) {
}

Identifier::~Identifier() {
}


std::string Identifier::token_literal() const {
    return token.literal + " " + value;
}

LetStatement::LetStatement(const Token& token):token(token), expression(nullptr) {

}

LetStatement::~LetStatement() {
    delete name;
}


std::string LetStatement::token_literal() const {
    return token.literal + " " + name->token_literal() + "\n";
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
