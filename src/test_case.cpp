#include "test_case.h"
#include <iostream>

namespace testing {
    TestCase::TestCase(const std::string& name):
        name(name) {

        }

    TestCase::~TestCase() {
        handle_test_end();
    }

    void TestCase::handle_test_end() const {
        if(pass) 
            std::cout << "[*] "  << name << " pass.\n";
        else
            std::cout << "[X] "  << name << " failed.\n";

    }
}
