#include "parser.h"

std::map<std::string, Parser::Precedence> Parser::precedence_map = {
    {token_type::EQ, Parser::Precedence::EQUALS}, // lower
    {token_type::NOT_EQ, Parser::Precedence::EQUALS},
    {token_type::LT, Parser::Precedence::LESS_GREATER},
    {token_type::GT, Parser::Precedence::LESS_GREATER},
    {token_type::PLUS, Parser::Precedence::SUM },
    {token_type::MINUS, Parser::Precedence::SUM },
    {token_type::SLASH, Parser::Precedence::PRODUCT},
    {token_type::ASTERISK, Parser::Precedence::PRODUCT},
};

Parser::Parser(Lexer* lexer):lexer(lexer) {
    next_token();
    next_token();

    prefix_expression_parsers[token_type::IDENT] = new IdentifierExpressionParser();
    prefix_expression_parsers[token_type::INT] = new IntegerExpressionParser();
    prefix_expression_parsers[token_type::BANG] = new PrefixTokenExpressionParser(this);
    prefix_expression_parsers[token_type::MINUS] = new PrefixTokenExpressionParser(this);

    prefix_expression_parsers[token_type::TRUE] = new BooleanExpressionParser(this);
    prefix_expression_parsers[token_type::FALSE] = new BooleanExpressionParser(this);


    prefix_expression_parsers[token_type::IF] = new IfExpressionParser(this);
    prefix_expression_parsers[token_type::LPAREN] = new GroupExpressionParser(this);
    prefix_expression_parsers[token_type::FUNCTION] = new FunctionalLiteralParser(this);


    infix_expression_parsers[token_type::PLUS] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::MINUS] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::SLASH] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::ASTERISK] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::EQ] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::NOT_EQ] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::LT] = new InfixTokenExpressionParser(this);
    infix_expression_parsers[token_type::GT] = new InfixTokenExpressionParser(this);


}

Parser::~Parser() {

}

Statement* Parser::parse_statement() {
    if(current_token.type == token_type::LET)
        return parse_let_statement();

    else if(current_token.type == token_type::RETURN)
        return parse_return_statement();

    return parse_expression_statement();
}

Statement* Parser::parse_let_statement() {
    // let x = 12;
    LetStatement* statement = new LetStatement(current_token);

    if(expect_peek(token_type::IDENT) == false) 
        return nullptr;

    statement->name = new Identifier(current_token, current_token.literal);

    if(expect_peek(token_type::ASSIGN) == false) 
        return nullptr;

    // move till ';' is found

    bool end_found = false;

    while(end_found == false) {
        if(current_token.type == token_type::SEMICOLON) {
            end_found = true;
            continue;
        }

        if(current_token.type == token_type::EOF_TYPE) {
            error_messages.push_back("';' missing in the end.");
            return nullptr;
        }

        next_token();

    }
    

    return statement;
}

Statement* Parser::parse_return_statement() {
    // return 123;
    ReturnStatement* statement = new ReturnStatement(current_token);
    next_token();


    // move till ';' is found

    bool end_found = false;

    while(end_found == false) {
        if(current_token.type == token_type::SEMICOLON) {
            end_found = true;
            continue;
        }

        if(current_token.type == token_type::EOF_TYPE) {
            error_messages.push_back("';' missing in the end.");
            return nullptr;
        }

        next_token();

    }
    

    return statement;
    
}




bool Parser::peek_token_is(const std::string& token_type) const {
    return peek_token.type == token_type;
}

bool Parser::expect_peek(const std::string& token_type) {
    if(peek_token_is(token_type)) {
        next_token();
        return true;
    }

    peek_error(token_type);
    return false;
}

void Parser::peek_error(const std::string& token_type)  {
    std::string message = "Expect peek token to be " + token_type + " got " + peek_token.type;
    error_messages.push_back(message);
}


bool Parser::current_token_is(const std::string& token_type) const {
    return current_token.type == token_type;
}

void Parser::next_token() {
    current_token = peek_token;
    peek_token = lexer->next_token();
}


Program* Parser::parse_program() {
    Program* program = new Program();

    while(current_token.type != token_type::EOF_TYPE) {
        Statement* statement = parse_statement();

        if(statement != nullptr)
            program->statements.push_back(statement);

        next_token();
    }

    return program;
}


ExpressionStatement* Parser::parse_expression_statement() {
    ExpressionStatement* statement = new ExpressionStatement(current_token);
    statement->expression = parse_expression(Precedence::LOWEST);

    if(peek_token_is(token_type::SEMICOLON)) 
        next_token();

    
    return statement;
}


Expression* Parser::parse_expression(const Precedence& precedence) {
    // 1 + 2
    if(prefix_expression_parsers.find(current_token.type) == prefix_expression_parsers.end())
        return nullptr;

    PrefixExpressionParser* prefix_express_parser =  prefix_expression_parsers[current_token.type];
    Expression* left_expression = prefix_express_parser->parse(current_token); // left = 1


    while(!peek_token_is(token_type::SEMICOLON) && precedence < peek_precedence()) {
        std::string peek_token_type = peek_token.type;

        auto it = infix_expression_parsers.find(peek_token_type); // infix parser for peek token '+'

        if(it == infix_expression_parsers.end())
            return left_expression;

        InfixTokenExpressionParser* infix_parser = it->second;
        next_token(); // current token now is '+'

        left_expression = infix_parser->parse(left_expression);

        


    }
    return left_expression;

}

Parser::Precedence Parser::peek_precedence() const {
    std::string peek_token_type = peek_token.type;
    auto it = precedence_map.find(peek_token_type);

    if(it == precedence_map.end())
        return Precedence::LOWEST;

    return it->second;
}


Parser::Precedence Parser::current_precedence() const {
    std::string current_token_type = current_token.type;
    auto it = precedence_map.find(current_token_type);

    if(it == precedence_map.end())
        return Precedence::LOWEST;

    return it->second;
}








