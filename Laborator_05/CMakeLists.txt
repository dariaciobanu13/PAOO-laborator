cmake_minimum_required(VERSION 3.13)
project(Laborator_05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(effective_cpp STATIC
    src/item10_return_this.cpp
    src/item11_autoatribuire.cpp
    src/item12_copiere_completa.cpp
)
target_include_directories(effective_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_options(effective_cpp PRIVATE -Wall -Wextra)

add_executable(Laborator_05 src/main.cpp)
target_link_libraries(Laborator_05 PRIVATE effective_cpp)
target_compile_options(Laborator_05 PRIVATE -Wall -Wextra)

# bad classes, address sanitizer catches the self-assignment bug
add_executable(demo_greseli src/demo_greseli.cpp)
target_link_libraries(demo_greseli PRIVATE effective_cpp)
target_compile_options(demo_greseli PRIVATE -O0 -g -fsanitize=address)
target_link_options(demo_greseli PRIVATE -fsanitize=address)
