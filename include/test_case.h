#ifndef TEST_CASE_H
#define TEST_CASE_H

#include <string>

namespace testing {
    struct TestCase {
        TestCase(const std::string& name);
        virtual ~TestCase();

        void handle_test_end() const;
        virtual void run() = 0;

        bool pass;
        std::string name;
    };

}

#endif
