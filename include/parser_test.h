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

    struct IfExpressionTest : TestCase {
        IfExpressionTest();
        virtual ~IfExpressionTest();

        virtual void run();

    };


    struct IfElseExpressionTest : TestCase {
        IfElseExpressionTest();
        virtual ~IfElseExpressionTest();

        virtual void run();

    };


    bool test_interger_expression_helper(Expression* expression, int value);
    bool test_identifier_expression_helper(Expression* expression, const std::string& value);
    bool test_boolean_expression_helper(Expression* expression, bool value);

    bool test_literal_expression(Expression* expression, int value);
    bool test_literal_expression(Expression* expression, const std::string& value);
    bool test_literal_expression(Expression* expression, bool  value);

    bool test_infix_expression(
            Expression* expression,
            const std::string& left,
            const std::string& operator_,
            const std::string& right
            );

    bool test_infix_expression(
            Expression* expression,
            int left,
            const std::string& operator_,
            int right
            );

    bool test_infix_expression(
            Expression* expression,
            bool left,
            const std::string& operator_,
            bool right
            );

    struct FunctionalLiteralTest : TestCase {
        FunctionalLiteralTest();
        virtual ~FunctionalLiteralTest();
        virtual void run();
    };

    struct FunctionParamaterTest : TestCase {
        FunctionParamaterTest();
        virtual ~FunctionParamaterTest();
        virtual void run();
    };
}

#endif
