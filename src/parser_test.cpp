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
                    const std::string& operator_
                    ): input(input), operator_(operator_) {}

            std::string input;
            std::string operator_;

            virtual void run(Expression* expression) = 0;
        };


        struct TestDataInt : TestData {
            TestDataInt(
                    const std::string& input,
                    const std::string& operator_,
                    int value
                    ):TestData(input, operator_), value(value) {}

            void run(Expression* expression) {
                PrefixTokenExpression* prefix_statement = dynamic_cast<PrefixTokenExpression*>(expression);

                if(prefix_statement->operator_ != operator_)
                    throw std::runtime_error("Expected prefix_token_expression.operator_ to be " + operator_ + " got " + prefix_statement->operator_);

                if(!test_literal_expression(prefix_statement->right, value))
                    throw std::runtime_error("prefix_token_expression.value did not match");

            }

            int value;
        };


        struct TestDataBool: TestData {
            TestDataBool(
                    const std::string& input,
                    const std::string& operator_,
                    bool value
                    ):TestData(input, operator_), value(value) {}

            void run(Expression* expression) {
                PrefixTokenExpression* prefix_statement = dynamic_cast<PrefixTokenExpression*>(expression);

                if(prefix_statement->operator_ != operator_)
                    throw std::runtime_error("Expected prefix_token_expression.operator_ to be " + operator_ + " got " + prefix_statement->operator_);

                if(!test_literal_expression(prefix_statement->right, value))
                    throw std::runtime_error("prefix_token_expression.value did not match");

            }

            bool value;
        };


        std::vector<TestData*> tests;
        tests.push_back(new TestDataInt("!3", "!", 3));
        tests.push_back(new TestDataInt("-7", "-", 7));
        tests.push_back(new TestDataBool("!true", "!", true));
        tests.push_back(new TestDataBool("!false", "!", false));

        for(TestData* test : tests) {

            Lexer* lexer = new Lexer(test->input);
            Parser* parser = new Parser(lexer);
            Program* program = parser->parse_program();

            if(program->statements.size() != 1) 
                throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

            ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
            test->run(expression_statement->expression);
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
                    const std::string& operator_
                    ):input(input),
            operator_(operator_) {}

            virtual void run(Expression* expression) = 0;

            std::string input;
            std::string operator_;
        };

        struct TestDataInt : TestData {
            TestDataInt(
                    const std::string& input,
                    int left_value,
                    const std::string& operator_,
                    int right_value
                    ):TestData(input, operator_),
            left_value(left_value),
            right_value(right_value) {}

            void run(Expression* expression) {

            if(!test_infix_expression(
                        expression,
                        left_value,
                        operator_,
                        right_value
                        ))  

                throw std::runtime_error("could not parse infix expression");

            }

            int left_value;
            int right_value;

        };


        struct TestDataBool : TestData {
            TestDataBool(
                    const std::string& input,
                    bool left_value,
                    const std::string& operator_,
                    bool right_value
                    ):TestData(input, operator_),
            left_value(left_value),
            right_value(right_value) {}

            void run(Expression* expression) {

            if(!test_infix_expression(
                        expression,
                        left_value,
                        operator_,
                        right_value
                        ))  

                throw std::runtime_error("could not parse infix expression");

            }

            bool left_value;
            bool right_value;

        };

        std::vector<TestData*> tests;
        tests.push_back(new TestDataInt("5 + 5", 5, "+" , 5));
        tests.push_back(new TestDataInt("5 - 5", 5, "-" , 5));
        tests.push_back(new TestDataInt("5 * 5", 5, "*", 5));
        tests.push_back(new TestDataInt("5 / 5", 5, "/", 5));
        tests.push_back(new TestDataInt("5 > 5", 5, ">", 5));
        tests.push_back(new TestDataInt("5 < 5", 5, "<", 5));
        tests.push_back(new TestDataInt("5 == 5", 5, "==", 5));
        tests.push_back(new TestDataInt("5 != 5", 5, "!=", 5));
        tests.push_back(new TestDataBool("true == true", true, "==", true));
        tests.push_back(new TestDataBool("false == false", false, "==", false));
        tests.push_back(new TestDataBool("true != false", true, "!=", false));

        for(TestData* test : tests) {

            Lexer* lexer = new Lexer(test->input);
            Parser* parser = new Parser(lexer);
            Program* program = parser->parse_program();

            if(program->statements.size() != 1) 
                throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

            ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
            test->run(expression_statement->expression);


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
			{"true", "true"},
			{"false", "false"},
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
			{"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
            // lparent tests
            {"1 + (2 + 3) + 4", "((1 + (2 + 3)) + 4)"},
			{"(5 + 5) * 2", "((5 + 5) * 2)"},
            {"2 / (5 + 5)", "(2 / (5 + 5))"},
            {"-(5 + 5)", "(-(5 + 5))"},
            {"!(true == true)", "(!(true == true))"}
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


    bool test_boolean_expression_helper(Expression* expression, bool  value) {
        BooleanExpression* boolean_exp = dynamic_cast<BooleanExpression*>(expression);

        if(boolean_exp->value != value) 
            return false;

        std::string value_str = value == true ? "true" : "false";


        if(boolean_exp->token_literal() != value_str) 
            return false;

        return true;

    }




    bool test_literal_expression(Expression* expression, int value) {
        return test_interger_expression_helper(expression, value);

    }

    bool test_literal_expression(Expression* expression, const std::string& value) {
        return test_identifier_expression_helper(expression, value);

    }

    bool test_literal_expression(Expression* expression, bool  value) {
        return test_boolean_expression_helper(expression, value);

    }


    bool test_infix_expression(
            Expression* expression,
            int left,
            const std::string& operator_,
            int right
            ) {

            InfixTokenExpression* infix_statement = dynamic_cast<InfixTokenExpression*>(expression);


            if(!test_literal_expression(infix_statement->left, left)) {
                std::cerr << "infix left did not match got " << infix_statement->left << " expected " << left << "\n";
                return false;
            }

            if(infix_statement->operator_ != operator_) {
                std::cerr << "infix operator did not match got " << infix_statement->operator_ << " expected " << operator_ << "\n";
                return false;
            }

            if(!test_literal_expression(infix_statement->right, right)) {
                std::cerr << "infix right did not match got " << infix_statement->right << " expected " << right << "\n";
                return false;
            }

        return true;
    }



    bool test_infix_expression(
            Expression* expression,
            bool left,
            const std::string& operator_,
            bool right
            ) {

            InfixTokenExpression* infix_statement = dynamic_cast<InfixTokenExpression*>(expression);


            if(!test_literal_expression(infix_statement->left, left)) {
                std::cerr << "infix left did not match got " << infix_statement->left << " expected " << left << "\n";
                return false;
            }

            if(infix_statement->operator_ != operator_) {
                std::cerr << "infix operator did not match got " << infix_statement->operator_ << " expected " << operator_ << "\n";
                return false;
            }

            if(!test_literal_expression(infix_statement->right, right)) {
                std::cerr << "infix right did not match got " << infix_statement->right << " expected " << right << "\n";
                return false;
            }

        return true;
    }

    bool test_infix_expression(
            Expression* expression,
            const std::string& left,
            const std::string& operator_,
            const std::string& right
            ) {

            InfixTokenExpression* infix_statement = dynamic_cast<InfixTokenExpression*>(expression);


            if(!test_literal_expression(infix_statement->left, left)) {
                std::cerr << "infix left did not match got " << infix_statement->left << " expected " << left << "\n";
                return false;
            }

            if(infix_statement->operator_ != operator_) {
                std::cerr << "infix operator did not match got " << infix_statement->operator_ << " expected " << operator_ << "\n";
                return false;
            }

            if(!test_literal_expression(infix_statement->right, right)) {
                std::cerr << "infix right did not match got " << infix_statement->right << " expected " << right << "\n";
                return false;
            }

        return true;
    }



    IfExpressionTest::IfExpressionTest():TestCase("If Test") {

    }

    IfExpressionTest::~IfExpressionTest() {

    }

    void IfExpressionTest::run() {
        std::string input = "if(x > y) { x }";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        IfExpression* if_expression = dynamic_cast<IfExpression*>(expression_statement->expression);

        if(!test_infix_expression(
                    if_expression->condition,
                    std::string("x"),
                    ">", 
                    std::string("y"))) 
            throw std::runtime_error("If condition parsing failed\n");

        int consequence_size = if_expression->consequence->statements.size();

        if(consequence_size != 1) 
            throw std::runtime_error("Expected 1 consequence, got " + std::to_string(consequence_size));


        expression_statement = dynamic_cast<ExpressionStatement*>(if_expression->consequence->statements[0]);

        if(!test_identifier_expression_helper(expression_statement->expression, std::string("x")))
            throw std::runtime_error("if identifer failed ");

        pass = true;


    }


    IfElseExpressionTest::IfElseExpressionTest():TestCase("If Else Test") {

    }

    IfElseExpressionTest::~IfElseExpressionTest() {

    }

    void IfElseExpressionTest::run() {
        std::string input = "if(x > y) { x } else { y }";

        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        IfExpression* if_expression = dynamic_cast<IfExpression*>(expression_statement->expression);

        if(!test_infix_expression(
                    if_expression->condition,
                    std::string("x"),
                    ">", 
                    std::string("y"))) 
            throw std::runtime_error("If condition parsing failed\n");

        int consequence_size = if_expression->consequence->statements.size();

        if(consequence_size != 1) 
            throw std::runtime_error("Expected 1 consequence, got " + std::to_string(consequence_size));


        expression_statement = dynamic_cast<ExpressionStatement*>(if_expression->consequence->statements[0]);

        if(!test_identifier_expression_helper(expression_statement->expression, std::string("x")))
            throw std::runtime_error("if identifer failed ");


        int alternative_size = if_expression->alternative->statements.size();

        if(alternative_size != 1) 
            throw std::runtime_error("Expected 1 alternative , got " + std::to_string(alternative_size));


        expression_statement = dynamic_cast<ExpressionStatement*>(if_expression->alternative->statements[0]);

        if(!test_identifier_expression_helper(expression_statement->expression, std::string("y")))
            throw std::runtime_error("if else identifer failed ");

        pass = true;


    }


    FunctionalLiteralTest::FunctionalLiteralTest():TestCase("Functional Literal Test") {

    }


    FunctionalLiteralTest::~FunctionalLiteralTest() {

    }

    void FunctionalLiteralTest::run() {
        std::string input = "fn(x,y) { x + y; }";
        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        FunctionalLiteral* func_literal = dynamic_cast<FunctionalLiteral*>(expression_statement->expression);

        int parameter_count = func_literal->parameters.size();

        if(parameter_count != 2) 
            throw std::runtime_error("Expected 2 parameters, got " + std::to_string(parameter_count));

        if(!test_literal_expression(func_literal->parameters[0], std::string("x"))) 
            throw std::runtime_error("Expected 'x' as  parameters, got " + func_literal->parameters[0]->string());

        if(!test_literal_expression(func_literal->parameters[1], std::string("y"))) 
            throw std::runtime_error("Expected 'y' as  parameters, got " + func_literal->parameters[1]->string());

        
        int block_statement_count = func_literal->body->statements.size();

        if(block_statement_count != 1) 
            throw std::runtime_error("Expected 1 block statement , got " + std::to_string(block_statement_count));

        
        expression_statement = dynamic_cast<ExpressionStatement*>(func_literal->body->statements[0]);


        if(test_infix_expression(expression_statement->expression, std::string("x"), "+", std::string("y")) == false)
            throw std::runtime_error("Function BlockStatement infix expression failed" );

        pass = true;
    }

    FunctionParamaterTest::FunctionParamaterTest():TestCase("Functional Parameter Test") {

    }


    FunctionParamaterTest::~FunctionParamaterTest() {

    }

    void FunctionParamaterTest::run() {
        struct TestData {
            TestData(const std::string& input, const std::vector<std::string>& parameters):
                input(input),
                parameters(parameters) {}

            virtual ~TestData() {}

            std::string input;
            std::vector<std::string> parameters;


        };

        std::vector<TestData> tests;
        tests.push_back(TestData("fn(){}", {}));
        tests.push_back(TestData("fn(x){}", {"x"}));
        tests.push_back(TestData("fn(x,y,z){}", {"x", "y", "z"}));

        for(TestData test : tests) {
            Lexer* lexer = new Lexer(test.input);
            Parser* parser = new Parser(lexer);
            Program* program = parser->parse_program();

            ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
            FunctionalLiteral* func_literal = dynamic_cast<FunctionalLiteral*>(expression_statement->expression);

            int parameter_count = func_literal->parameters.size();

            if(parameter_count != test.parameters.size()) 
                throw std::runtime_error("Function parameter count does not match got " + std::to_string(parameter_count) + " expected " + std::to_string(test.parameters.size()));

        }

        pass = true;

    }

    CallExpressionTest::CallExpressionTest():TestCase("Call Expression Test") {

    }

    CallExpressionTest::~CallExpressionTest() {

    }

    void CallExpressionTest::run() {
        std::string input = "add(1, 1 + 5, 7 * 5)";
        Lexer* lexer = new Lexer(input);
        Parser* parser = new Parser(lexer);
        Program* program = parser->parse_program();

        if(program->statements.size() != 1) 
            throw std::runtime_error("Expected 1 statements, got " + std::to_string(program->statements.size()));

        ExpressionStatement* expression_statement = dynamic_cast<ExpressionStatement*>(program->statements[0]);
        CallExpression * call_expression = dynamic_cast<CallExpression*>(expression_statement->expression);

        int argument_count = call_expression->arguments.size();

        if(argument_count != 3) 
            throw std::runtime_error("Expected 3 arguments, got " + std::to_string(argument_count));

        if(!test_literal_expression(call_expression->arguments[0], 1)) 
            throw std::runtime_error("First argument did not match in call expresion");


        if(!test_infix_expression(call_expression->arguments[1], 1, "+", 5)) 
            throw std::runtime_error("Second argument did not match in call expresion");

        if(!test_infix_expression(call_expression->arguments[2], 7, "*", 5)) 
            throw std::runtime_error("Third argument did not match in call expresion");

        

        pass = true;
    }


}
