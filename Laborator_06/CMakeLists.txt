cmake_minimum_required(VERSION 3.13)
project(Laborator_06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(effective_cpp STATIC
    src/contract.cpp
    src/vestiar.cpp
    src/item13_raii.cpp
    src/item14_copiere_raii.cpp
)
target_include_directories(effective_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_options(effective_cpp PRIVATE -Wall -Wextra)

add_executable(Laborator_06 src/main.cpp)
target_link_libraries(Laborator_06 PRIVATE effective_cpp)
target_compile_options(Laborator_06 PRIVATE -Wall -Wextra)

# bad versions, address sanitizer reports the leak at exit
add_executable(demo_greseli src/demo_greseli.cpp)
target_link_libraries(demo_greseli PRIVATE effective_cpp)
target_compile_options(demo_greseli PRIVATE -O0 -g -fsanitize=address)
target_link_options(demo_greseli PRIVATE -fsanitize=address)
