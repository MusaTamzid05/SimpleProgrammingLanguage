#include <iostream>
#include <vector>
#include <stdexcept>
#include "lexer.h"
#include "lexer_test.h"
#include "parser_test.h"
#include "parser.h"

void run_tests();
void run_repl();

int main(int argc, char** argv) {
    if(argc == 2) {
        if(argv[1] == std::string("test")) 
            run_tests();

        return 0;
    }
    run_repl();

    return 0;
}


void run_tests() {
    std::vector<testing::TestCase*> tests;
    tests.push_back(new testing::NextTokenTest1());
    tests.push_back(new testing::NextTokenTest2());
    tests.push_back(new testing::ParseLetStatementIdentifierTest());
    tests.push_back(new testing::ReturnStatementTest());
    tests.push_back(new testing::IdentifierExpressionTest());
    tests.push_back(new testing::IntegerExpressionTest());
    tests.push_back(new testing::PrefixTokenExpressionTest());
    tests.push_back(new testing::InfixTokenExpressionTest());
    tests.push_back(new testing::OperatorPrecedenceTest());

    for(testing::TestCase* test : tests) {
        try {
            test->run();
        } catch(std::runtime_error& err) {
            std::cerr << err.what() <<  "\n";
        }

        delete test;

    }

}

void run_repl() {
    bool running = true;
    std::string input;

    while(running) {
        std::cout << ">>> ";
        std::getline(std::cin, input);

        if(input == "exit") {
            running = false;
            continue;
        }

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        for(std::string error_message : parser->error_messages) 
            std::cerr << error_message << "\n";

        /*
        for(Statement* statement : program->statements) 
            std::cout  << statement->token_literal() << "\n";
        */

        std::cout << program->string() << "\n";
        


        

    }

}
