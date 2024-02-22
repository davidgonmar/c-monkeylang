cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_SOURCE_DIR}/src)


add_executable(test_lexer test_lexer.c)


target_link_libraries(test_lexer Unity)
target_link_libraries(test_lexer monkeylang)

add_test(test_lexer test_lexer)
