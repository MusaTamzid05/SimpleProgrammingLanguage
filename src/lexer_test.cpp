#include "lexer_test.h"
#include <vector>
#include "lexer.h"
#include "lexer_test.h"
#include <stdexcept>

namespace testing {
    NextTokenTest1::NextTokenTest1():TestCase("Next Token Test 1") {

    }

    NextTokenTest1::~NextTokenTest1() {

    }

    void NextTokenTest1::run() {
        Lexer lexer("(){};=");
        std::vector<Token> tests = {
            Token(token_type::LPAREN, "("),
            Token(token_type::RPAREN, ")"),
            Token(token_type::LBRACE, "{"),
            Token(token_type::RBRACE, "}"),
            Token(token_type::SEMICOLON, ";"),
            Token(token_type::ASSIGN, "="),
        };

        for(Token expected_token : tests) {
            Token predicted_token = lexer.next_token();

            if(predicted_token.type != expected_token.type) {
                throw std::runtime_error("Expected type " + expected_token.type + " got " + predicted_token.type);
            }

            if(predicted_token.literal != expected_token.literal) {
                throw std::runtime_error("Expected literal " + expected_token.literal+ " got " + predicted_token.literal);
            }


        }

        pass = true;

    }


    NextTokenTest2::NextTokenTest2():TestCase("Next Token Test 2") {

    }

    NextTokenTest2::~NextTokenTest2() {

    }

    void NextTokenTest2::run() {
        std::string input = R"(let five = 5;
        let ten = 10;

        let add = fn(x, y) {
          x + y;
        };

        let result = add(five, ten);

        !-/*5;
        5 < 10 > 5;

        if (5 < 10) {
            return true;
        } else {
            return false;
        }

        10 == 10;
        10 != 9;
        )";

        Lexer lexer(input);
        std::vector<Token> tests = {
            {token_type::LET, "let"},
            {token_type::IDENT, "five"},
            {token_type::ASSIGN, "="},
            {token_type::INT, "5"},
            {token_type::SEMICOLON, ";"},
            {token_type::LET, "let"},
            {token_type::IDENT, "ten"},
            {token_type::ASSIGN, "="},
            {token_type::INT, "10"},
            {token_type::SEMICOLON, ";"},
            {token_type::LET, "let"},
            {token_type::IDENT, "add"},
            {token_type::ASSIGN, "="},
            {token_type::FUNCTION, "fn"},
            {token_type::LPAREN, "("},
            {token_type::IDENT, "x"},
            {token_type::COMMA, ","},
            {token_type::IDENT, "y"},
            {token_type::RPAREN, ")"},
            {token_type::LBRACE, "{"},
            {token_type::IDENT, "x"},
            {token_type::PLUS, "+"},
            {token_type::IDENT, "y"},
            {token_type::SEMICOLON, ";"},
            {token_type::RBRACE, "}"},
            {token_type::SEMICOLON, ";"},
            {token_type::LET, "let"},
            {token_type::IDENT, "result"},
            {token_type::ASSIGN, "="},
            {token_type::IDENT, "add"},
            {token_type::LPAREN, "("},
            {token_type::IDENT, "five"},
            {token_type::COMMA, ","},
            {token_type::IDENT, "ten"},
            {token_type::RPAREN, ")"},
            {token_type::SEMICOLON, ";"},


            {token_type::BANG, "!"},
            {token_type::MINUS, "-"},
            {token_type::SLASH, "/"},
            {token_type::ASTERISK, "*"},
            {token_type::INT, "5"},
            {token_type::SEMICOLON, ";"},
            {token_type::INT, "5"},
            {token_type::LT, "<"},
            {token_type::INT, "10"},
            {token_type::GT, ">"},
            {token_type::INT, "5"},
            {token_type::SEMICOLON, ";"},
            {token_type::IF, "if"},
            {token_type::LPAREN, "("},
            {token_type::INT, "5"},
            {token_type::LT, "<"},
            {token_type::INT, "10"},
            {token_type::RPAREN, ")"},
            {token_type::LBRACE, "{"},
            {token_type::RETURN, "return"},
            {token_type::TRUE, "true"},
            {token_type::SEMICOLON, ";"},
            {token_type::RBRACE, "}"},
            {token_type::ELSE, "else"},
            {token_type::LBRACE, "{"},
            {token_type::RETURN, "return"},
            {token_type::FALSE, "false"},
            {token_type::SEMICOLON, ";"},
            {token_type::RBRACE, "}"},
            {token_type::INT, "10"},
            {token_type::EQ, "=="},
            {token_type::INT, "10"},
            {token_type::SEMICOLON, ";"},
            {token_type::INT, "10"},
            {token_type::NOT_EQ, "!="},
            {token_type::INT, "9"},
            {token_type::SEMICOLON, ";"},
            {token_type::EOF_TYPE, ""}
        };


        for(Token expected_token : tests) {
            Token predicted_token = lexer.next_token();

            if(predicted_token.type != expected_token.type) {
                throw std::runtime_error("Expected type " + expected_token.type + " got " + predicted_token.type);
            }

            if(predicted_token.literal != expected_token.literal) {
                throw std::runtime_error("Expected literal " + expected_token.literal+ " got " + predicted_token.literal);
            }


        }

        pass = true;

    }


}
