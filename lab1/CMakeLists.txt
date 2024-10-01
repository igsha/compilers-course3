cmake_minimum_required(VERSION 3.29)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
project(lab1 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_MODULE_STD 1)

add_library(lexer lexer.cpp detail/tokentype.cpp detail/states.cpp)
target_include_directories(lexer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(lab1 main.cpp)
target_link_libraries(lab1 lexer)

add_test(NAME lab1::number COMMAND lab1 "12.73e-5")
set_tests_properties(lab1::number PROPERTIES PASS_REGULAR_EXPRESSION "Number \\[12\\.73e-5\\]")

add_test(NAME lab1::several COMMAND lab1 "12.56 558.49e-+9")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Number \\[12.56\\]")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Blank \\[ \\]")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Number \\[558\\.49\\]")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Id \\[a\\]")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Operator \\[-\\]")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Operator \\[+\\]")
set_tests_properties(lab1::several PROPERTIES PASS_REGULAR_EXPRESSION "Number \\[9\\]")
