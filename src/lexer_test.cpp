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
            {token_type::SEMICOLON, ";"}
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
