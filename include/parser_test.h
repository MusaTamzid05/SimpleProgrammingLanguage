#ifndef PARSER_TEST_H
#define PARSER_TEST_H

#include "test_case.h"
#include "ast.h"

namespace testing {
    struct ParseLetStatementIdentifierTest : TestCase {
        ParseLetStatementIdentifierTest();
        virtual ~ParseLetStatementIdentifierTest();

        bool test_let_statement(Statement* statement, const std::string& expected_idenitifer);
        virtual void run();
    };


    struct ReturnStatementTest : TestCase {
        ReturnStatementTest();
        virtual ~ReturnStatementTest();

        virtual void run();
    };


    struct IdentifierExpressionTest: TestCase {
        IdentifierExpressionTest();
        virtual ~IdentifierExpressionTest();

        virtual void run();
    };


}

#endif
