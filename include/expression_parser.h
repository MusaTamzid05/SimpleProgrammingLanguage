#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "ast.h"

struct Parser;


struct PrefixExpressionParser {
    virtual Expression* parse(const Token& token) = 0;
};

struct IdentifierExpressionParser : PrefixExpressionParser {
    IdentifierExpressionParser();
    virtual ~IdentifierExpressionParser();

    Expression* parse(const Token& token);
};


struct IntegerExpressionParser : PrefixExpressionParser {
    IntegerExpressionParser();
    virtual ~IntegerExpressionParser();

    Expression* parse(const Token& token);

};

struct GroupExpressionParser : PrefixExpressionParser {
    GroupExpressionParser(Parser* parser);
    virtual ~GroupExpressionParser();

    Expression* parse(const Token& token);
    Parser* parser;

};


struct PrefixTokenExpressionParser : PrefixExpressionParser {
    PrefixTokenExpressionParser(Parser* parser);
    virtual ~PrefixTokenExpressionParser();

    Expression* parse(const Token& token);
    Parser* parser;

};

struct BlockStatementParser {
    BlockStatementParser(Parser* parser);
    virtual ~BlockStatementParser();

    BlockStatement* parse(const Token& token);

    Parser* parser;

};

struct IfExpressionParser  : PrefixExpressionParser {
    IfExpressionParser(Parser* parser);
    virtual ~IfExpressionParser();

    Expression* parse(const Token& token);
    Parser* parser;

};


struct InfixTokenExpressionParser {
    InfixTokenExpressionParser(Parser* parser);
    virtual ~InfixTokenExpressionParser();

    virtual Expression* parse(Expression* left);
    Parser* parser;

};


struct BooleanExpressionParser: PrefixExpressionParser {
    BooleanExpressionParser(Parser* parser);
    virtual ~BooleanExpressionParser();

    Expression* parse(const Token& token);
    Parser* parser;

};

struct FunctionalLiteralParser : PrefixExpressionParser {

    // parsing parameter can fail, have to return
    // something that can flag this, hense
    // the data type below
    struct ParseParameterResponse {
        std::vector<Identifier*> identifiers;
        bool success;
    };


    FunctionalLiteralParser(Parser* parser);
    virtual ~FunctionalLiteralParser();

    ParseParameterResponse  parse_parameters() const;

    Expression* parse(const Token& token);
    Parser* parser;
};


struct CallExpressionParser : InfixTokenExpressionParser {
    struct ParseArgumentResult {
        std::vector<Expression*> arguments;
        bool success;
    };

    CallExpressionParser(Parser* parser);
    virtual ~CallExpressionParser();

    Expression* parse(Expression* left);
    ParseArgumentResult parse_arguments();
};





#endif
