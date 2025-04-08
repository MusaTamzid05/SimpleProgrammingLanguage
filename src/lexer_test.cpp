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

}
