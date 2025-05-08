#include "parser_test.h"
#include "lexer.h"
#include "parser.h"
#include <stdexcept>
#include <iostream>

namespace testing {
    ParseLetStatementIdentifierTest::ParseLetStatementIdentifierTest():TestCase("LetStatement Identifier Test") {
    }

    ParseLetStatementIdentifierTest::~ParseLetStatementIdentifierTest() {
    }

    void ParseLetStatementIdentifierTest::run() {
        std::string input = R"(
            let x = 5;
            let y = 10;
            let foobar = 838383;
            )";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 3) 
            throw std::runtime_error("Expected 3 statements, got " + std::to_string(program->statements.size()));

        std::vector<std::string> tests = {"x", "y", "foobar"};

        for(unsigned int i = 0; i < tests.size(); i += 1) {
            if(!test_let_statement(program->statements[i], tests[i]))
                return;

        }

        pass = true;


    }

    bool ParseLetStatementIdentifierTest::test_let_statement(Statement* statement, const std::string& expected_idenitifer) {
        if(statement->token_literal() != "let") {
            std::cerr << "Expected first token to be let, got " << statement->token_literal() << "\n";
            return false;
        }

        LetStatement* let_statement = dynamic_cast<LetStatement*>(statement);

        if(let_statement->name->value != expected_idenitifer) {
            std::cerr << "Expected idenifier value to be " << expected_idenitifer << " got " << let_statement->name->value;
            return false;
        }

        if(let_statement->name->token_literal() != expected_idenitifer) {
            std::cerr << "Expected idenifier token_literal to be " << expected_idenitifer << " got " << let_statement->name->token_literal();
            return false;
        }

        return true;
    }


    ReturnStatementTest::ReturnStatementTest():TestCase("ReturnStatement Test") {

    }

    ReturnStatementTest::~ReturnStatementTest() {

    }

    void ReturnStatementTest::run() {
        std::string input = R"(
            return x;
            return 10;
            return  foobar;
            )";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 3) 
            throw std::runtime_error("Expected 3 statements, got " + std::to_string(program->statements.size()));

        std::vector<std::string> tests = {"x", "10", "foobar"};

        for(unsigned int i = 0; i < tests.size(); i += 1) {
            Statement* statement = program->statements[i];
            ReturnStatement* return_statement = dynamic_cast<ReturnStatement*>(statement);

            if(return_statement->token_literal() != "return") 
                throw std::runtime_error("Expected token literal to be 'return' got " + return_statement->token_literal());


        }

        pass = true;
    }


    IdentifierExpressionTest::IdentifierExpressionTest():TestCase("IdentiferExpressionStatement Test") {

    }

    IdentifierExpressionTest::~IdentifierExpressionTest() {

    }

    void IdentifierExpressionTest::run() {
        std::string input = "foobar;";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        Identifier* identifier = dynamic_cast<Identifier*>(expression_statement->expression);


        if(identifier->value != "foobar") 
            throw std::runtime_error("Expected identifier.value to be 'foobar', got " + identifier->value);

        if(identifier->token_literal()!= "foobar") 
            throw std::runtime_error("Expected identifier.token_literal() to be 'foobar', got " + identifier->token_literal());



        pass = true;
    }



}
