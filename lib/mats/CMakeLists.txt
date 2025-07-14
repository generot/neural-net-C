cmake_minimum_required(VERSION 3.10)
project(Mats LANGUAGES C)

set(M_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(M_INC_DIR "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(M_SOURCES 
    ${M_SRC_DIR}/matrix.c
)

add_library(mats STATIC ${M_SOURCES})

target_include_directories(mats PUBLIC ${M_INC_DIR})
target_compile_options(mats PRIVATE -Wall -Wextra -Werror -Wpedantic -g)