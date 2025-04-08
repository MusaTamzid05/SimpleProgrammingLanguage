#include <iostream>
#include <vector>
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
        test->run();
        delete test;

    }

}
