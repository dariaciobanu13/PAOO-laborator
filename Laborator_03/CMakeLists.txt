cmake_minimum_required(VERSION 3.13)
project(Laborator_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# static library with the Echipa class
add_library(echipa STATIC src/echipa.cpp)
target_include_directories(echipa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_options(echipa PRIVATE -Wall -Wextra)

# main program (the correct version)
add_executable(Laborator_03 src/main.cpp)
target_link_libraries(Laborator_03 PRIVATE echipa)
target_compile_options(Laborator_03 PRIVATE -Wall -Wextra)

# program with the bad classes
# built with address sanitizer so the memory errors actually show up
add_executable(fotbal_bug src/demo_bug.cpp)
target_include_directories(fotbal_bug PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_options(fotbal_bug PRIVATE -g -fsanitize=address)
target_link_options(fotbal_bug PRIVATE -fsanitize=address)
