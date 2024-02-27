cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_SOURCE_DIR}/src)


add_executable(test_lexer test_lexer.c)
add_executable(test_token test_token.c)
add_executable(test_ast test_ast.c)

target_link_libraries(test_lexer Unity)
target_link_libraries(test_lexer monkeylang)
target_link_libraries(test_token Unity)
target_link_libraries(test_token monkeylang)
target_link_libraries(test_ast Unity)
target_link_libraries(test_ast monkeylang)

add_test(test_lexer test_lexer)
add_test(test_token test_token)
add_test(test_ast test_ast)