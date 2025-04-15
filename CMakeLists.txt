cmake_minimum_required(VERSION 3.0)

project(simple)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


SET(SOURCE_FILES
    src/main.cpp
    src/token.cpp
    src/lexer.cpp
    src/test_case.cpp
    src/lexer_test.cpp
    src/ast.cpp
    )



add_executable(simple ${SOURCE_FILES})

include_directories(include)
target_link_libraries(simple)
