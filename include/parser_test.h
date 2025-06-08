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

    struct IntegerExpressionTest: TestCase {
        IntegerExpressionTest();
        virtual ~IntegerExpressionTest();

        virtual void run();
    };

    bool test_interger_expression_helper(Expression* expression, int value);


    struct PrefixTokenExpressionTest: TestCase {
        PrefixTokenExpressionTest();
        virtual ~PrefixTokenExpressionTest();

        virtual void run();
    };


    struct InfixTokenExpressionTest: TestCase {
        InfixTokenExpressionTest();
        virtual ~InfixTokenExpressionTest();

        virtual void run();
    };


    struct OperatorPrecedenceTest : TestCase {
        OperatorPrecedenceTest();
        virtual ~OperatorPrecedenceTest();
        virtual void run();

    };
}

#endif
