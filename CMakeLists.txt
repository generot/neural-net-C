cmake_minimum_required(VERSION 3.10)
project(NeuralNetwork LANGUAGES C)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

set(SOURCES 
    ${SRC_DIR}/main.c
)

add_executable(neural_net ${SOURCES})
add_subdirectory("./lib")

target_include_directories(neural_net PRIVATE ${INC_DIR})
target_link_libraries(neural_net PRIVATE mats)

target_compile_options(neural_net PUBLIC -Wall -Wextra -Werror -Wpedantic -g)