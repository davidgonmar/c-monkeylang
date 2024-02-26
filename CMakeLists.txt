cmake_minimum_required(VERSION 3.0)

project(MyProject)


include(CTest)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

add_executable(repl src/repl.c)

target_link_libraries(repl monkeylang)