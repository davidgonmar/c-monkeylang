cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE SRC_FILES "*.c")

add_library(monkeylang ${SRC_FILES})