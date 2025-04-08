#include <iostream>
#include <vector>
#include <stdexcept>
#include "lexer.h"
#include "lexer_test.h"

void run_tests();
void run_repl();

int main(int argc, char** argv) {
    run_repl();
    return 0;
}


void run_tests() {
    std::vector<testing::TestCase*> tests;
    tests.push_back(new testing::NextTokenTest1());

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

        Lexer lexer(input);

        bool file_end_found = false;

        while(file_end_found == false) {
            Token token = lexer.next_token();

            std::cout << "type " << token.type << " literal " << token.literal << "\n";

            if(token.type == token_type::EOF_TYPE) 
                file_end_found = true;

        }
        

    }

}
