#ifndef LEXER_TEST_H
#define LEXER_TEST_H

#include "test_case.h"

namespace testing {
    struct NextTokenTest1 : TestCase {
        NextTokenTest1();
        virtual ~NextTokenTest1();

        virtual void run();
    };

    struct NextTokenTest2 : TestCase {
        NextTokenTest2();
        virtual ~NextTokenTest2();

        virtual void run();
    };

}

#endif
