cmake_minimum_required(VERSION 3.0.0)
project(EEG VERSION 0.1.0)

add_executable(${PROJECT_NAME} src/main.cpp
							   include/FFT.hpp )

target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11
												 CXX_STANDARD 14
												 CXX_STANDARD 17
												 CXX_STANDARD_REQUIRED ON)

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:CLANG>>:-Wall -Wextra -pedantic>                                                             $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
