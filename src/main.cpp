#include <iostream>
#include <vector>
#include <stdexcept>
#include "lexer_test.h"

void run_tests();

int main(int argc, char** argv) {
    run_tests();
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
