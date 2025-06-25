#include "parser_test.h"
#include "lexer.h"
#include "parser.h"
#include <stdexcept>
#include <iostream>

namespace testing {
    ParseLetStatementIdentifierTest::ParseLetStatementIdentifierTest():TestCase("LetStatement Identifier Test") {
    }

    ParseLetStatementIdentifierTest::~ParseLetStatementIdentifierTest() {
    }

    void ParseLetStatementIdentifierTest::run() {
        std::string input = R"(
            let x = 5;
            let y = 10;
            let foobar = 838383;
            )";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 3) 
            throw std::runtime_error("Expected 3 statements, got " + std::to_string(program->statements.size()));

        std::vector<std::string> tests = {"x", "y", "foobar"};

        for(unsigned int i = 0; i < tests.size(); i += 1) {
            if(!test_let_statement(program->statements[i], tests[i]))
                return;

        }

        pass = true;


    }

    bool ParseLetStatementIdentifierTest::test_let_statement(Statement* statement, const std::string& expected_idenitifer) {
        if(statement->token_literal() != "let") {
            std::cerr << "Expected first token to be let, got " << statement->token_literal() << "\n";
            return false;
        }

        LetStatement* let_statement = dynamic_cast<LetStatement*>(statement);

        if(let_statement->name->value != expected_idenitifer) {
            std::cerr << "Expected idenifier value to be " << expected_idenitifer << " got " << let_statement->name->value;
            return false;
        }

        if(let_statement->name->token_literal() != expected_idenitifer) {
            std::cerr << "Expected idenifier token_literal to be " << expected_idenitifer << " got " << let_statement->name->token_literal();
            return false;
        }

        return true;
    }


    ReturnStatementTest::ReturnStatementTest():TestCase("ReturnStatement Test") {

    }

    ReturnStatementTest::~ReturnStatementTest() {

    }

    void ReturnStatementTest::run() {
        std::string input = R"(
            return x;
            return 10;
            return  foobar;
            )";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 3) 
            throw std::runtime_error("Expected 3 statements, got " + std::to_string(program->statements.size()));

        std::vector<std::string> tests = {"x", "10", "foobar"};

        for(unsigned int i = 0; i < tests.size(); i += 1) {
            Statement* statement = program->statements[i];
            ReturnStatement* return_statement = dynamic_cast<ReturnStatement*>(statement);

            if(return_statement->token_literal() != "return") 
                throw std::runtime_error("Expected token literal to be 'return' got " + return_statement->token_literal());


        }

        pass = true;
    }


    IdentifierExpressionTest::IdentifierExpressionTest():TestCase("IdentiferExpressionStatement Test") {

    }

    IdentifierExpressionTest::~IdentifierExpressionTest() {

    }

    void IdentifierExpressionTest::run() {
        std::string input = "foobar;";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        Identifier* identifier = dynamic_cast<Identifier*>(expression_statement->expression);


        if(identifier->value != "foobar") 
            throw std::runtime_error("Expected identifier.value to be 'foobar', got " + identifier->value);

        if(identifier->token_literal()!= "foobar") 
            throw std::runtime_error("Expected identifier.token_literal() to be 'foobar', got " + identifier->token_literal());



        pass = true;
    }


    IntegerExpressionTest::IntegerExpressionTest():TestCase("IntergerExpressionStatement Test") {

    }

    IntegerExpressionTest::~IntegerExpressionTest() {

    }

    void IntegerExpressionTest::run() {
        std::string input = "5;";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        IntegerLiteral* literal = dynamic_cast<IntegerLiteral*>(expression_statement->expression);


        if(literal->value != 5) 
            throw std::runtime_error("Expected interger_literal.value to be '5', got " + std::to_string(literal->value));

        if(literal->token_literal()!= "5") 
            throw std::runtime_error("Expected identifier.token_literal() to be '5', got " + literal->token_literal());



        pass = true;
    }

    bool test_interger_expression_helper(Expression* expression, int value) {
        IntegerLiteral* literal = dynamic_cast<IntegerLiteral*>(expression);

        if(literal->value != value) 
            return false;

        if(literal->token_literal() != std::to_string(value)) 
            return false;

        return true;

    }

    PrefixTokenExpressionTest::PrefixTokenExpressionTest():TestCase("PrefixTokenExpressionTest Test") {

    }

    PrefixTokenExpressionTest::~PrefixTokenExpressionTest() {

    }

    void PrefixTokenExpressionTest::run() {

        struct TestData {
            TestData(
                    const std::string& input,
                    const std::string& operator_,
                    int value
                    ):input(input), operator_(operator_), value(value) {}

            std::string input;
            std::string operator_;
            int value;
        };

        std::vector<TestData> tests;
        tests.push_back(TestData("!3", "!", 3));
        tests.push_back(TestData("-7", "-", 7));

        for(TestData test : tests) {

            Lexer* lexer = new Lexer(test.input);
            Parser* parser = new Parser(lexer);
            Program* program = parser->parse_program();

            if(program->statements.size() != 1) 
                throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

            ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
            PrefixTokenExpression* prefix_statement = dynamic_cast<PrefixTokenExpression*>(expression_statement->expression);

            if(prefix_statement->operator_ != test.operator_)
                throw std::runtime_error("Expected prefix_token_expression.operator_ to be " + test.operator_ + " got " + prefix_statement->operator_);

            if(!test_interger_expression_helper(prefix_statement->right, test.value))
                throw std::runtime_error("prefix_token_expression.value did not match");
        }

        pass = true;


    }


    InfixTokenExpressionTest::InfixTokenExpressionTest():TestCase("Infix token test") {

    }

    InfixTokenExpressionTest::~InfixTokenExpressionTest() {

    }

    void InfixTokenExpressionTest::run() {

        struct TestData {
            TestData(
                    const std::string& input,
                    int left_value,
                    const std::string& operator_,
                    int right_value
                    ):input(input),
            left_value(left_value),
            operator_(operator_),
            right_value(right_value) {}

            std::string input;
            int left_value;
            std::string operator_;
            int right_value;
        };

        std::vector<TestData> tests;
        tests.push_back(TestData("5 + 5", 5, "+" , 5));
        tests.push_back(TestData("5 - 5", 5, "-" , 5));
        tests.push_back(TestData("5 * 5", 5, "*", 5));
        tests.push_back(TestData("5 / 5", 5, "/", 5));
        tests.push_back(TestData("5 > 5", 5, ">", 5));
        tests.push_back(TestData("5 < 5", 5, "<", 5));
        tests.push_back(TestData("5 == 5", 5, "==", 5));
        tests.push_back(TestData("5 != 5", 5, "!=", 5));

        for(TestData test : tests) {

            Lexer* lexer = new Lexer(test.input);
            Parser* parser = new Parser(lexer);
            Program* program = parser->parse_program();

            if(program->statements.size() != 1) 
                throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

            ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);

            if(!test_infix_expression(
                        expression_statement->expression,
                        test.left_value,
                        test.operator_,
                        test.right_value
                        ))  

                throw std::runtime_error("could not parse infix expression");

            /*
            InfixTokenExpression* infix_statement = dynamic_cast<InfixTokenExpression*>(expression_statement->expression);


            if(!test_interger_expression_helper(infix_statement->left, test.left_value))
                throw std::runtime_error("infix left did not match");

            if(infix_statement->operator_ != test.operator_)
                throw std::runtime_error("infix operator did not match");

            if(!test_interger_expression_helper(infix_statement->right, test.right_value))
                throw std::runtime_error("infix right did not match");
                */
        }

        pass = true;


    }

    OperatorPrecedenceTest::OperatorPrecedenceTest():TestCase("Operator Precedence Test") {

    }



    OperatorPrecedenceTest::~OperatorPrecedenceTest() {

    }

    void OperatorPrecedenceTest::run() {
        struct OperatorPrecedenceTestData {
            std::string input;
            std::string output;
        };

        std::vector<OperatorPrecedenceTestData> tests = {
			{"-a * b", "((-a) * b)"},
			{"!-a", "(!(-a))"},
			{"a + b + c", "((a + b) + c)"},
			{"a + b - c", "((a + b) - c)"},
			{"a * b * c", "((a * b) * c)"},
			{"a * b / c", "((a * b) / c)"},
			{"a + b / c", "(a + (b / c))"},
			{"a + b * c + d / e - f", "(((a + (b * c)) + (d / e)) - f)"},
			{"3 + 4; -5 * 5", "(3 + 4)((-5) * 5)"},
			{"5 > 4 == 3 < 4", "((5 > 4) == (3 < 4))"},
			{"5 < 4 != 3 > 4", "((5 < 4) != (3 > 4))"},
			{"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
			{"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"}
		};

        for(OperatorPrecedenceTestData test : tests) {
            Lexer* lexer = new Lexer(test.input);
            Parser* parser = new Parser(lexer);
            Program* program = parser->parse_program();

            std::string actual = program->string();

            if(actual != test.output)
                throw std::runtime_error("Expected =>" + test.output +  " actual =>" + actual );
        }

        pass = true;
    }



    bool test_identifier_expression_helper(Expression* expression, const std::string& value) {
        Identifier* idenifier = dynamic_cast<Identifier*>(expression);

        if(idenifier->value != value) 
            return false;

        if(idenifier->token_literal() != value) 
            return false;

        return true;

    }



    bool test_literal_expression(Expression* expression, int value) {
        return test_interger_expression_helper(expression, value);

    }

    bool test_literal_expression(Expression* expression, const std::string& value) {
        return test_literal_expression(expression, value);

    }


    bool test_infix_expression(
            Expression* expression,
            int left,
            const std::string& operator_,
            int right
            ) {

            InfixTokenExpression* infix_statement = dynamic_cast<InfixTokenExpression*>(expression);


            if(!test_literal_expression(infix_statement->left, left)) {
                std::cerr << "infix left did not match\n" ;
                return false;
            }

            if(infix_statement->operator_ != operator_) {
                std::cerr << "infix operator did not match\n";
                return false;
            }

            if(!test_literal_expression(infix_statement->right, right)) {
                std::cerr << "infix right did not match\n";
                return false;
            }

        return true;
    }








}
